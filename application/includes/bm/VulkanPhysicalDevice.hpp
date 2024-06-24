#pragma once

#include "bm/VulkanInstance.hpp"
#include "bm/VulkanWindowSurface.hpp"

namespace bm {
    class VulkanPhysicalDevice {
    public:
        using Ptr = std::shared_ptr<VulkanPhysicalDevice>;

        VulkanPhysicalDevice(VulkanInstance::Ptr InInstance, VulkanWindowSurface::Ptr InSurface);
        ~VulkanPhysicalDevice();

        bool Initialize();
        void Deinitialize();

        bool CreateDevice(vk::Device& InDevice, const vk::DeviceCreateInfo& InCreateInfo);

        [[nodiscard]] bool IsInitialized() const { return mInitialized; }

        [[nodiscard]] const vk::PhysicalDeviceFeatures& GetFeatures() const { return mDeviceFeatures; }

        VulkanInstance::Ptr GetInstance() { return mInstance; }

        const std::vector<const char*>& GetEnabledLayers() const { return mEnabledLayers; }
        const std::vector<const char*>& GetEnabledExtensions() const { return mEnabledExtensions; }

        std::uint32_t GetQueueFamilyIndex() const { return mQueueFamilyIndex; }
        std::uint32_t GetQueueCount() const { return mQueueCount; }

    private:
        bool IsDeviceSuitable(const vk::PhysicalDevice& InDevice);

        std::uint32_t mQueueFamilyIndex;
        std::uint32_t mQueueCount;

        bool mInitialized;
        VulkanInstance::Ptr mInstance;
        VulkanWindowSurface::Ptr mSurface;
        vk::PhysicalDevice mDevice;
        vk::PhysicalDeviceFeatures mDeviceFeatures;

        std::vector<vk::LayerProperties> mLayersProperties;
        std::vector<vk::ExtensionProperties> mExtensionsProperties;

        std::vector<const char*> mEnabledLayers;
        std::vector<const char*> mEnabledExtensions;
    };
}