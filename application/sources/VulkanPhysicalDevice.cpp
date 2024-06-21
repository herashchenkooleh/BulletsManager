#include "bm/VulkanPhysicalDevice.hpp"
#include "bm/Logger.hpp"

#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>
#include <vulkan/vulkan_enums.hpp>

namespace bm {
    VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance::Ptr InInstance)
        : mInitialized(false)
        , mInstance(InInstance) {

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

        std::vector<vk::QueueFamilyProperties> QueueFamiliesProperties = mDevice.getQueueFamilyProperties();
        std::uint32_t Index = 0;
        for (auto& QueueFamilyProperties: QueueFamiliesProperties) {
            if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eGraphics) {
                mQueueFamilies.insert({ vk::QueueFlagBits::eGraphics, { QueueFamilyProperties.queueFlags, QueueFamilyProperties.queueCount, Index } });
            }

            if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eCompute) {
                mQueueFamilies.insert({ vk::QueueFlagBits::eCompute, { QueueFamilyProperties.queueFlags, QueueFamilyProperties.queueCount, Index } });
            }

            if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eProtected) {
                mQueueFamilies.insert({ vk::QueueFlagBits::eProtected, { QueueFamilyProperties.queueFlags, QueueFamilyProperties.queueCount, Index } });
            }

            if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eTransfer) {
                mQueueFamilies.insert({ vk::QueueFlagBits::eTransfer, { QueueFamilyProperties.queueFlags, QueueFamilyProperties.queueCount, Index } });
            }

            if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eSparseBinding) {
                mQueueFamilies.insert({ vk::QueueFlagBits::eSparseBinding, { QueueFamilyProperties.queueFlags, QueueFamilyProperties.queueCount, Index } });
            }

            if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eOpticalFlowNV) {
                mQueueFamilies.insert({ vk::QueueFlagBits::eOpticalFlowNV, { QueueFamilyProperties.queueFlags, QueueFamilyProperties.queueCount, Index } });
            }

            if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eVideoDecodeKHR) {
                mQueueFamilies.insert({ vk::QueueFlagBits::eVideoDecodeKHR, { QueueFamilyProperties.queueFlags, QueueFamilyProperties.queueCount, Index } });
            }

            if (QueueFamilyProperties.queueFlags & vk::QueueFlagBits::eVideoEncodeKHR) {
                mQueueFamilies.insert({ vk::QueueFlagBits::eVideoEncodeKHR, { QueueFamilyProperties.queueFlags, QueueFamilyProperties.queueCount, Index } });
            }

            Index++;
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
            return true;
        }

        return false;
    }

    const VulkanPhysicalDevice::QueueFamily& VulkanPhysicalDevice::GetQueueFamily(const vk::QueueFlagBits& InFlags) const {
        if (decltype(auto) Iter = mQueueFamilies.find(InFlags); Iter != mQueueFamilies.end()) {
            return Iter->second;
        }

        static QueueFamily sEmptyQueueFamily {};
        return sEmptyQueueFamily;
    }
}