
#include "bm/Configs.hpp"
#include <vulkan/vulkan.hpp>

#if __APPLE__
    #include <MoltenVK/mvk_vulkan.h>
    #include <vulkan/vulkan_metal.h>
#endif

namespace bm {
    /*static*/ std::string Configs::sGlobalWindowTitle = "global.window_title";
    /*static*/ std::string Configs::sGlobalApplicationName = "global.appplication_name";
    /*static*/ std::string Configs::sGlobalApplicationVersion = "global.application_version";
    /*static*/ std::string Configs::sGlobalEngineName = "global.engine_name";
    /*static*/ std::string Configs::sGlobalEngineVersion = "global.engine_version";
    /*static*/ std::string Configs::sGlobalRenderApiName = "global.render_api_name";
    /*static*/ std::string Configs::sGlobalRenderApiVersion = "global.render_api_version";
    /*static*/ std::string Configs::sGlobalRenderApiExtensions = "global.render_api_extensions";
    /*static*/ std::string Configs::sGlobalRenderApiLayers = "global.render_api_layers";

    /*static*/ Configs& Configs::GetInstance() {
        static Configs sInstance;
        return sInstance;
    }

    Configs::Configs() {
        //TODO: read configs from lua database
        Set<std::string>(sGlobalWindowTitle, "BulletManager");
        Set<std::string>(sGlobalApplicationName, "BulletManagerApp");
        Set<std::uint32_t>(sGlobalApplicationVersion, VK_MAKE_VERSION(0, 1, 0));
        Set<std::string>(sGlobalEngineName, "CustomEngine");
        Set<std::uint32_t>(sGlobalEngineVersion, VK_MAKE_VERSION(0, 1, 0));
        Set<std::string>(sGlobalRenderApiName, "vulkan");
        Set<std::uint32_t>(sGlobalRenderApiVersion, VK_API_VERSION_1_3);
        Set<std::vector<const char*>>(sGlobalRenderApiExtensions, {
#if defined(VK_USE_PLATFORM_METAL_EXT)
            VK_EXT_METAL_SURFACE_EXTENSION_NAME,
#endif

#ifdef DEBUG
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
#endif
            VK_KHR_SURFACE_EXTENSION_NAME,
            VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
        });
        Set<std::vector<const char*>>(sGlobalRenderApiLayers, {
#ifdef DEBUG
            "VK_LAYER_KHRONOS_validation"
#endif
        });
    }
}