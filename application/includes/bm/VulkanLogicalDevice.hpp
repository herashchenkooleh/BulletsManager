#pragma once

#include "bm/VulkanPhysicalDevice.hpp"
#include <vulkan/vulkan_metal.h>

namespace bm {
    class VulkanLogicalDevice {
    public:
        using Ptr = std::shared_ptr<VulkanLogicalDevice>;

        VulkanLogicalDevice(VulkanPhysicalDevice::Ptr InPhysDevice);
        ~VulkanLogicalDevice();

        bool Initialize();
        void Deinitialize();

        VulkanPhysicalDevice::Ptr GetPhysicalDevice() { return mPhysDevice; }

    private:
        VulkanPhysicalDevice::Ptr mPhysDevice;
        vk::Device mDevice;
        float mQueuePriority;
        vk::Queue mQueue;

        vk::SurfaceKHR mSurface;
        CAMetalLayer* caMetalLayer;
    };
}