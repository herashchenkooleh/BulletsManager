
#include "bm/Configs.hpp"
#include <vulkan/vulkan.hpp>

namespace bm {
    /*static*/ std::string Configs::sGlobalWindowTitle = "global.window_title";
    /*static*/ std::string Configs::sGlobalApplicationName = "global.appplication_name";
    /*static*/ std::string Configs::sGlobalApplicationVersion = "global.application_version";
    /*static*/ std::string Configs::sGlobalEngineName = "global.engine_name";
    /*static*/ std::string Configs::sGlobalEngineVersion = "global.engine_version";
    /*static*/ std::string Configs::sGlobalRenderApiName = "global.render_api_name";
    /*static*/ std::string Configs::sGlobalRenderApiVersion = "global.render_api_version";

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
    }
}