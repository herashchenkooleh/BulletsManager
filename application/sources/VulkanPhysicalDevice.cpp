#include "bm/VulkanPhysicalDevice.hpp"
#include "bm/Logger.hpp"

#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>
#include <vulkan/vulkan_enums.hpp>

namespace bm {
    VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance::Ptr InInstance, VulkanWindowSurface::Ptr InSurface)
        : mInitialized(false)
        , mInstance(InInstance)
        , mSurface(InSurface) {

    }

    VulkanPhysicalDevice::~VulkanPhysicalDevice() = default;

    bool VulkanPhysicalDevice::Initialize() {
        if (!mInstance) {
            return mInitialized;
        }

        decltype(auto) PhysicalDevices = mInstance->GetPhysicalDevices();
        for (auto& PhysDevice: PhysicalDevices) {
            if (IsDeviceSuitable(PhysDevice)) {
                Logger::GetInstance().Debug("Found suitable vulkan physical device");
                mDevice = PhysDevice;
                mInitialized = true;
                break;
            }
        }

        mDeviceFeatures = mDevice.getFeatures();
        mLayersProperties = mDevice.enumerateDeviceLayerProperties(mInstance->GetLoader());
        for (const auto& LayerProperty: mLayersProperties) {
            mEnabledLayers.push_back(LayerProperty.layerName);
            mExtensionsProperties = mDevice.enumerateDeviceExtensionProperties(std::string{LayerProperty.layerName }, mInstance->GetLoader());
            for (const auto& ExtensionProperty: mExtensionsProperties) {
                mEnabledExtensions.push_back(ExtensionProperty.extensionName);
            }
        }
#ifdef DEBUG
        mEnabledExtensions.push_back("VK_KHR_portability_subset");
#endif

        return mInitialized;
    }

    void VulkanPhysicalDevice::Deinitialize() {

    }

    bool VulkanPhysicalDevice::CreateDevice(vk::Device& InDevice, const vk::DeviceCreateInfo& InCreateInfo) {
        return vk::Result::eSuccess == mDevice.createDevice(&InCreateInfo, &mInstance->GetAllocator(), &InDevice, mInstance->GetLoader());
    }

    bool VulkanPhysicalDevice::IsDeviceSuitable(const vk::PhysicalDevice& InDevice) {
        decltype(auto) Properties = InDevice.getProperties();
        if (Properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu ||
            Properties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu) {

            std::vector<vk::QueueFamilyProperties> QueueFamiliesProperties = InDevice.getQueueFamilyProperties();
            std::uint32_t Index = 0;
            for (auto& QueueFamilyProperties: QueueFamiliesProperties) {
                if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eGraphics) {
                    vk::Bool32 PresentSupport = false;
                    vk::Result Status = InDevice.getSurfaceSupportKHR(Index, mSurface->GetVulkanSurface(), &PresentSupport, mInstance->GetLoader());
                    if (Status == vk::Result::eSuccess && PresentSupport) {
                        mQueueFamilyIndex = Index;
                        mQueueCount = QueueFamilyProperties.queueCount;
                        return true;
                    }
                }
            }
        }

        return false;
    }
}