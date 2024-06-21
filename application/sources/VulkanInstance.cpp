#include "bm/VulkanInstance.hpp"
#include "bm/Configs.hpp"
#include "vulkan/vulkan_extension_inspection.hpp"
#include "bm/Logger.hpp"
#include <vulkan/vulkan_enums.hpp>

namespace bm {
    VulkanInstance::VulkanInstance()
        : mInitialized(false){

    }

    VulkanInstance::~VulkanInstance() = default;

    bool VulkanInstance::Initialize() {
        Logger::GetInstance().Debug("Requested render API: %s", Configs::GetInstance().Get<std::string>(Configs::sGlobalRenderApiName));
        Logger::GetInstance().Debug("Requested render API version: %d", Configs::GetInstance().Get<std::uint32_t>(Configs::sGlobalRenderApiVersion));

        mAppInfo =  {
            .pApplicationName = Configs::GetInstance().Get<std::string>(Configs::sGlobalApplicationName).c_str(),
            .applicationVersion = Configs::GetInstance().Get<std::uint32_t>(Configs::sGlobalApplicationVersion),
            .pEngineName = Configs::GetInstance().Get<std::string>(Configs::sGlobalEngineName).c_str(),
            .engineVersion = Configs::GetInstance().Get<std::uint32_t>(Configs::sGlobalEngineVersion),
            .apiVersion = Configs::GetInstance().Get<std::uint32_t>(Configs::sGlobalRenderApiVersion)
        };

        std::vector<vk::ExtensionProperties> SupportedExtensions = vk::enumerateInstanceExtensionProperties();
#ifdef  DEBUG
        for (const auto& Extension: SupportedExtensions) {
            Logger::GetInstance().Debug("Supported extension: %s", Extension.extensionName);
        }
#endif
        decltype(auto) NeedExtensions = Configs::GetInstance().Get<std::vector<const char*>>(Configs::sGlobalRenderApiExtensions);
        decltype(auto) SupportedExtensionsBegin = std::cbegin(SupportedExtensions);
        decltype(auto) SupportedExtensionsEnd = std::cend(SupportedExtensions);
        for (const auto& NeedExtension: NeedExtensions)
        {
            decltype(auto) ExtensionIter = std::find_if(SupportedExtensionsBegin, SupportedExtensionsEnd,
                [NeedExtension](const vk::ExtensionProperties& InProp) {
                    return std::strcmp(NeedExtension, InProp.extensionName.data()) == 0;
                });
            if (ExtensionIter == SupportedExtensionsEnd) {
                Logger::GetInstance().Fatal("Unsupported render api extension: ", NeedExtension);
                return false;
            }
            mEnabledExtensions.push_back(NeedExtension);
        };

        decltype(auto) SupportedLayers = vk::enumerateInstanceLayerProperties();
#ifdef  DEBUG
        for (const auto& Layer: SupportedLayers) {
            Logger::GetInstance().Debug("Supported layer: %s", Layer.layerName);
        }
#endif
        decltype(auto) NeedLayers = Configs::GetInstance().Get<std::vector<const char*>>(Configs::sGlobalRenderApiLayers);
        decltype(auto) SupportedLayersBegin = std::cbegin(SupportedLayers);
        decltype(auto) SupportedLayersEnd = std::cend(SupportedLayers);
        for (const auto& NeedLayer: NeedLayers) {
            decltype(auto) LayerIter = std::find_if(SupportedLayersBegin, SupportedLayersEnd,
                            [NeedLayer](const vk::LayerProperties& InProp) {
                                return std::strcmp(NeedLayer, InProp.layerName.data()) == 0;
                            });
            if (LayerIter == SupportedLayersEnd) {
                Logger::GetInstance().Fatal("Unsupported render api layer: ", NeedLayer);
                return false;
            }

            mEnabledLayers.push_back(NeedLayer);
        }

        mCreateInfo = {
            .pApplicationInfo = &mAppInfo,
            .enabledLayerCount = static_cast<std::uint32_t>(NeedLayers.size()),
            .ppEnabledLayerNames = NeedLayers.data(),
            .enabledExtensionCount = static_cast<std::uint32_t>(NeedExtensions.size()),
            .ppEnabledExtensionNames = NeedExtensions.data(),
           .flags = vk::InstanceCreateFlags{ vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR }
        };

        vk::Result Status = vk::createInstance(&mCreateInfo, &mAllocCallbacks, &mInstance);
        mInitialized = Status == vk::Result::eSuccess;

        if (!mInitialized) {
            return mInitialized;
        }

        mLoader.init(mInstance, mDynLoader.getProcAddress<PFN_vkGetInstanceProcAddr>("vkGetInstanceProcAddr"));

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
            .pfnUserCallback = &VulkanInstance::DebugCallback,
            .pUserData = nullptr
        };

        Status = mInstance.createDebugUtilsMessengerEXT(&mDebugCreateInfo, &mAllocCallbacks, &mDebugMessenger, mLoader);
        mInitialized = mInitialized && (Status == vk::Result::eSuccess);
        if (!mInitialized) {
            Logger::GetInstance().Error("Failed initialize debug messanger");
        }
#endif

        return mInitialized;
    }

    void VulkanInstance::Deinitialize() {
        mInstance.destroyDebugUtilsMessengerEXT(mDebugMessenger, mAllocCallbacks, mLoader);
        mInstance.destroy(mAllocCallbacks);
    }

    VulkanInstance::PhysicalDevicesList VulkanInstance::GetPhysicalDevices() const {
        if (!IsInitialized()) {
            return {};
        }

        return mInstance.enumeratePhysicalDevices(mLoader);
    }

#ifdef DEBUG
    /*static*/ VkBool32 VulkanInstance::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT InMessageSeverity,
                                                      VkDebugUtilsMessageTypeFlagsEXT InMessageType,
                                                      const VkDebugUtilsMessengerCallbackDataEXT* InCallbackData,
                                                      void* InUserData) {

        if (InMessageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
            Logger::GetInstance().Trace("Vulkan message: %s", InCallbackData->pMessage);
        }
        else if (InMessageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
            Logger::GetInstance().Debug("Vulkan message: %s", InCallbackData->pMessage);
        }
        else if (InMessageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            Logger::GetInstance().Warning("Vulkan message: %s", InCallbackData->pMessage);
        }
        else if (InMessageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            Logger::GetInstance().Error("Vulkan message: %s", InCallbackData->pMessage);
        }

        return VK_FALSE;
    }
#endif
}