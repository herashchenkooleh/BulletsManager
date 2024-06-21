#pragma once

#include "bm/VulkanInstance.hpp"

namespace bm {
    class VulkanPhysicalDevice {
    public:
        struct QueueFamily {
            vk::QueueFlags mFlags;
            std::uint32_t mQueueCount;
            std::uint32_t mIndex;
        };

        using Ptr = std::shared_ptr<VulkanPhysicalDevice>;

        VulkanPhysicalDevice(VulkanInstance::Ptr InInstance);
        ~VulkanPhysicalDevice();

        bool Initialize();
        void Deinitialize();

        bool CreateDevice(vk::Device& InDevice, const vk::DeviceCreateInfo& InCreateInfo);

        [[nodiscard]] bool IsInitialized() const { return mInitialized; }

        [[nodiscard]] const QueueFamily& GetQueueFamily(const vk::QueueFlagBits& InFlags) const;



        [[nodiscard]] const vk::PhysicalDeviceFeatures& GetFeatures() const { return mDeviceFeatures; }

        VulkanInstance::Ptr GetInstance() { return mInstance; }

        const std::vector<const char*>& GetEnabledLayers() const { return mEnabledLayers; }
        const std::vector<const char*>& GetEnabledExtensions() const { return mEnabledExtensions; }

    private:
        bool IsDeviceSuitable(const vk::PhysicalDevice& InDevice);

        bool mInitialized;
        VulkanInstance::Ptr mInstance;
        vk::PhysicalDevice mDevice;
        vk::PhysicalDeviceFeatures mDeviceFeatures;

        std::unordered_map<vk::QueueFlagBits, QueueFamily> mQueueFamilies;

        std::vector<vk::LayerProperties> mLayersProperties;
        std::vector<vk::ExtensionProperties> mExtensionsProperties;

        std::vector<const char*> mEnabledLayers;
        std::vector<const char*> mEnabledExtensions;
    };
}