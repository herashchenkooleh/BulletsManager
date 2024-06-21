#pragma once
#include <any>
#include <map>
#include <string>

namespace bm {
    class Configs {
    public:
        static std::string sGlobalWindowTitle;
        static std::string sGlobalApplicationName;
        static std::string sGlobalApplicationVersion;
        static std::string sGlobalEngineName;
        static std::string sGlobalEngineVersion;
        static std::string sGlobalRenderApiName;
        static std::string sGlobalRenderApiVersion;
        static std::string sGlobalRenderApiExtensions;
        static std::string sGlobalRenderApiLayers;

        static Configs& GetInstance();

        Configs(const Configs& InObject) = delete;
        Configs& operator=(const Configs& InObject) = delete;

        template<typename Type>
        void Set(const std::string& InParam, std::remove_reference_t<Type>&& InValue) {
            std::any Value = { std::forward<Type>(InValue) };
            m_Value.emplace(InParam, Value);
        }

        template<typename Type>
        Type Get(const std::string& InParam) const {
            if (decltype(auto) Param = m_Value.find(InParam); Param != m_Value.cend()) {
                if (Param->second.has_value()) {
                    return std::any_cast<Type>(Param->second);
                }
            }
            return Type{};
        }

    private:
        Configs();

        using ParamsMap = std::map<std::string, std::any>;

        ParamsMap m_Value;
    };
}
