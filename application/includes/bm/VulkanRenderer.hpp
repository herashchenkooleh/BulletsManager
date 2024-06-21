#pragma once

#include "bm/Renderer.hpp"
#include "bm/VulkanInstance.hpp"
#include "bm/VulkanPhysicalDevice.hpp"
#include "bm/VulkanLogicalDevice.hpp"
#include "bm/VulkanWindowSurface.hpp"

namespace bm {
    class VulkanRenderer : public Renderer {
    public:
        VulkanRenderer(Window::Ptr InWindow);
        ~VulkanRenderer() override;

        bool Initialize() override;
        void Update() override;
        void Deinitialize() override;

        [[nodiscard]] bool IsInitialized() const override { return mInitialized; }

    private:
        bool mInitialized;
        Window::Ptr mWindow;
        VulkanInstance::Ptr mInstance;
        VulkanPhysicalDevice::Ptr mPhysicalDevice;
        VulkanLogicalDevice::Ptr mLogicalDevice;
        VulkanWindowSurface::Ptr mSurface;
    };
}
