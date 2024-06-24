#include "bm/VulkanLogicalDevice.hpp"
#include "bm/Logger.hpp"

#if __APPLE__
    #include <MoltenVK/mvk_vulkan.h>
    #include <vulkan/vulkan_metal.h>
#endif

#include "GLFW/glfw3.h"

namespace bm {
    VulkanLogicalDevice::VulkanLogicalDevice(VulkanPhysicalDevice::Ptr InPhysDevice)
        : mPhysDevice(InPhysDevice){

    }

    VulkanLogicalDevice::~VulkanLogicalDevice() = default;

    bool VulkanLogicalDevice::Initialize() {
        vk::DeviceQueueCreateInfo QueueCreateInfo = {
            .flags = vk::DeviceQueueCreateFlags { },
            .queueFamilyIndex = mPhysDevice->GetQueueFamilyIndex(),
            .queueCount = mPhysDevice->GetQueueCount(),
            .pQueuePriorities = &mQueuePriority
        };

        decltype(auto) EnabledLayers = mPhysDevice->GetEnabledLayers();
        decltype(auto) EnabledExtensions = mPhysDevice->GetEnabledExtensions();

        vk::DeviceCreateInfo CreateInfo = {
            .flags = vk::DeviceCreateFlags { },
            .pQueueCreateInfos = &QueueCreateInfo,
            .queueCreateInfoCount = 1,
            .pEnabledFeatures = &mPhysDevice->GetFeatures(),
            .ppEnabledLayerNames = EnabledLayers.data(),
            .enabledLayerCount = static_cast<std::uint32_t>(EnabledLayers.size()),
            .ppEnabledExtensionNames = EnabledExtensions.data(),
            .enabledExtensionCount = static_cast<std::uint32_t>(EnabledExtensions.size())
        };

        if (!mPhysDevice->CreateDevice(mDevice, CreateInfo)) {
            Logger::GetInstance().Fatal("Failed initialize vulkan logical device");
            return false;
        }

        mDevice.getQueue(mPhysDevice->GetQueueFamilyIndex(), 0, &mQueue, mPhysDevice->GetInstance()->GetLoader());
        return true;
    }

    void VulkanLogicalDevice::Deinitialize() {
        mDevice.destroy(mPhysDevice->GetInstance()->GetAllocator());
    }

}