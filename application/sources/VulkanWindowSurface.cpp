#include "bm/VulkanWindowSurface.hpp"
#include "GLFW/glfw3.h"

namespace bm {
    VulkanWindowSurface::VulkanWindowSurface(Window::Ptr InWindow, VulkanInstance::Ptr InInstance)
        : mWindow(InWindow)
        , mInstance(InInstance) {

    }
    VulkanWindowSurface::~VulkanWindowSurface() = default;

    bool VulkanWindowSurface::Initialize() {
        GLFWwindow* Window = reinterpret_cast<GLFWwindow*>(mWindow->GetRenderTargetHandle());
        glfwCreateWindowSurface(mInstance->GetVulkanInstance(), Window, reinterpret_cast<VkAllocationCallbacks*>(&mInstance->GetAllocator()), reinterpret_cast<VkSurfaceKHR*>(&mSurface));
        return true;
    }

    void VulkanWindowSurface::Deinitialize() {

    }
}