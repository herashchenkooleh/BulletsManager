#pragma once

#include "Renderer.hpp"

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>


namespace bm {
    class VulkanRenderer : public Renderer {
    public:
        VulkanRenderer();
        ~VulkanRenderer() override;

        bool Initialize() override;
        void Update() override;
        void Deinitialize() override;

        [[nodiscard]] bool IsInitialized() const override { return mInitialized; }

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

#ifdef DEBUG
        vk::DebugUtilsMessengerCreateInfoEXT mDebugCreateInfo;
#endif
    };
}
