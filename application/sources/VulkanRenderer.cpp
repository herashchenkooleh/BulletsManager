#include "bm/VulkanRenderer.hpp"

namespace bm {
    VulkanRenderer::VulkanRenderer(Window::Ptr InWindow)
        : mInitialized(false)
        , mWindow(InWindow)
        , mInstance(std::make_shared<VulkanInstance>())
        , mPhysicalDevice(std::make_shared<VulkanPhysicalDevice>(mInstance))
        , mLogicalDevice(std::make_shared<VulkanLogicalDevice>(mPhysicalDevice))
        , mSurface(std::make_shared<VulkanWindowSurface>(mWindow, mInstance)) {
    }

    VulkanRenderer::~VulkanRenderer() /*override*/ = default;

    bool VulkanRenderer::Initialize() /*override*/ {
        mInitialized = mInstance->Initialize();
        mInitialized = mInitialized && mPhysicalDevice->Initialize();
        mInitialized = mInitialized && mLogicalDevice->Initialize();
        mInitialized = mInitialized && mSurface->Initialize();

        return mInitialized;
    }

    void VulkanRenderer::Update() /*override*/ {

    }

    void VulkanRenderer::Deinitialize() /*override*/ {
        mLogicalDevice->Deinitialize();
        mPhysicalDevice->Deinitialize();
        mInstance->Deinitialize();
    }
}