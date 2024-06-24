#include "bm/VulkanRenderer.hpp"

namespace bm {
    VulkanRenderer::VulkanRenderer(Window::Ptr InWindow)
        : mInitialized(false)
        , mWindow(InWindow)
        , mInstance(std::make_shared<VulkanInstance>())
        , mSurface(std::make_shared<VulkanWindowSurface>(mWindow, mInstance))
        , mPhysicalDevice(std::make_shared<VulkanPhysicalDevice>(mInstance, mSurface))
        , mLogicalDevice(std::make_shared<VulkanLogicalDevice>(mPhysicalDevice)) {
    }

    VulkanRenderer::~VulkanRenderer() /*override*/ = default;

    bool VulkanRenderer::Initialize() /*override*/ {
        mInitialized = mInstance->Initialize();
        mInitialized = mInitialized && mSurface->Initialize();
        mInitialized = mInitialized && mPhysicalDevice->Initialize();
        mInitialized = mInitialized && mLogicalDevice->Initialize();

        return mInitialized;
    }

    void VulkanRenderer::Update() /*override*/ {

    }

    void VulkanRenderer::Deinitialize() /*override*/ {
        mLogicalDevice->Deinitialize();
        mPhysicalDevice->Deinitialize();
        mSurface->Deinitialize();
        mInstance->Deinitialize();
    }
}