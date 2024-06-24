#pragma once

#include <memory>
#include <vulkan/vulkan.hpp>
#include "Window.hpp"
#include "bm/VulkanInstance.hpp"

namespace bm {
    class VulkanWindowSurface {
    public:
        using Ptr = std::shared_ptr<VulkanWindowSurface>;

        VulkanWindowSurface(Window::Ptr InWindow, VulkanInstance::Ptr InInstance);
        ~VulkanWindowSurface();

        bool Initialize();
        void Deinitialize();

        vk::SurfaceKHR& GetVulkanSurface() { return mSurface; }

    private:
        vk::SurfaceKHR mSurface;
        Window::Ptr mWindow;
        VulkanInstance::Ptr mInstance;
    };
}
