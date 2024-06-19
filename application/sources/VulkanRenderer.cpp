#include "bm/VulkanRenderer.hpp"
#include "bm/Configs.hpp"
#include "vulkan/vulkan_extension_inspection.hpp"
#include "bm/Logger.hpp"
#include <vulkan/vulkan_enums.hpp>

namespace bm {
    VulkanRenderer::VulkanRenderer()
        : mInitialized(false) {
    }

    VulkanRenderer::~VulkanRenderer() /*override*/ = default;

    bool VulkanRenderer::Initialize() /*override*/ {
        Logger::GetInstance().Debug("Requested render API: %s", Configs::GetInstance().Get<std::string>(Configs::sGlobalRenderApiName));
        Logger::GetInstance().Debug("Requested render API version: %d", Configs::GetInstance().Get<std::uint32_t>(Configs::sGlobalRenderApiVersion));

        mAppInfo =  {
            .pApplicationName = Configs::GetInstance().Get<std::string>(Configs::sGlobalApplicationName).c_str(),
            .applicationVersion = Configs::GetInstance().Get<std::uint32_t>(Configs::sGlobalApplicationVersion),
            .pEngineName = Configs::GetInstance().Get<std::string>(Configs::sGlobalEngineName).c_str(),
            .engineVersion = Configs::GetInstance().Get<std::uint32_t>(Configs::sGlobalEngineVersion),
            .apiVersion = Configs::GetInstance().Get<std::uint32_t>(Configs::sGlobalRenderApiVersion)
        };

        decltype(auto) SupportedExtensions = vk::getInstanceExtensions();

        for (const auto& Extension: SupportedExtensions) {
            Logger::GetInstance().Debug("Supported extension: %s", Extension);
        }

        std::vector<const char*> Extensions
        {
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
        };

        std::vector<const char*> Layers
        {
            "VK_LAYER_KHRONOS_validation"
        };

        mCreateInfo = {
            .pApplicationInfo = &mAppInfo,
            .enabledLayerCount = static_cast<std::uint32_t>(Layers.size()),
            .ppEnabledLayerNames = Layers.data(),
            .enabledExtensionCount = static_cast<std::uint32_t>(Extensions.size()),
            .ppEnabledExtensionNames = Extensions.data(),
           .flags = vk::InstanceCreateFlags{ vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR }
        };

        vk::Result Status = vk::createInstance(&mCreateInfo, &mAllocCallbacks, &mInstance);
        mInitialized = Status == vk::Result::eSuccess;

#ifdef DEBUG
        mDebugCreateInfo = {
            .flags = vk::DebugUtilsMessengerCreateFlagsEXT{
            },
            .messageSeverity = vk::DebugUtilsMessageSeverityFlagsEXT {
               vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
               vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
               vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
               vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
            },
            .messageType = vk::DebugUtilsMessageTypeFlagsEXT {
                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eDeviceAddressBinding
            },
            .pfnUserCallback = &VulkanRenderer::DebugCallback,
            .pUserData = nullptr
        };
#endif

        return mInitialized;
    }

    void VulkanRenderer::Update() /*override*/ {

    }

    void VulkanRenderer::Deinitialize() /*override*/ {

    }

#ifdef DEBUG
    /*static*/ VkBool32 VulkanRenderer::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT InMessageSeverity,
                                                      VkDebugUtilsMessageTypeFlagsEXT InMessageType,
                                                      const VkDebugUtilsMessengerCallbackDataEXT* InCallbackData,
                                                      void* InUserData) {

        if (InMessageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
            Logger::GetInstance().Trace("Vulkan message: ", InCallbackData->pMessage);
        }
        else if (InMessageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
            Logger::GetInstance().Debug("Vulkan message: ", InCallbackData->pMessage);
        }
        else if (InMessageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            Logger::GetInstance().Warning("Vulkan message: ", InCallbackData->pMessage);
        }
        else if (InMessageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            Logger::GetInstance().Error("Vulkan message: ", InCallbackData->pMessage);
        }

    }
#endif
}