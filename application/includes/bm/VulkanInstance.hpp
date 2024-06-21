#pragma once

#include <vulkan/vulkan.hpp>

namespace bm {
    class VulkanInstance {
    public:
        using Ptr = std::shared_ptr<VulkanInstance>;
        using PhysicalDevicesList = std::vector<vk::PhysicalDevice>;

        VulkanInstance();
        ~VulkanInstance();

        bool Initialize();
        void Deinitialize();

        [[nodiscard]] bool IsInitialized() const { return mInitialized; }

        PhysicalDevicesList GetPhysicalDevices() const;

        const std::vector<const char*>& GetEnabledLayers() const { return mEnabledLayers; }
        const std::vector<const char*>& GetEnabledExtensions() const { return mEnabledExtensions; }

        vk::AllocationCallbacks& GetAllocator() { return mAllocCallbacks; }
        const vk::AllocationCallbacks& GetAllocator() const { return mAllocCallbacks; }

        vk::DispatchLoaderDynamic& GetLoader() { return mLoader; }
        const vk::DispatchLoaderDynamic& GetLoader() const { return mLoader; }

        vk::Instance& GetVulkanInstance() { return mInstance; }


#ifdef DEBUG
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT InMessageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT InMessageType,
            const VkDebugUtilsMessengerCallbackDataEXT* InCallbackData,
            void* InUserData);
#endif

    private:
        bool mInitialized;

        vk::ApplicationInfo mAppInfo;
        vk::AllocationCallbacks mAllocCallbacks;
        vk::Instance mInstance;
        vk::InstanceCreateInfo mCreateInfo;
        vk::DispatchLoaderDynamic mLoader;
        vk::DynamicLoader mDynLoader;
#ifdef DEBUG
        vk::DebugUtilsMessengerCreateInfoEXT mDebugCreateInfo;
        vk::DebugUtilsMessengerEXT mDebugMessenger;
#endif

        std::vector<const char*> mEnabledLayers;
        std::vector<const char*> mEnabledExtensions;
    };
}