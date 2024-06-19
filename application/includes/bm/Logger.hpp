#pragma once

#include <string>
#include <boost/log/trivial.hpp>
#include <boost/format.hpp>

namespace bm {
    class Logger {
    public:
        enum class Level
        {
            Trace,
            Debug,
            Info,
            Warning,
            Error,
            Fatal
        };

        static Logger& GetInstance();

        Logger(const Logger& InObject) = delete;
        Logger& operator=(const Logger& InObject) = delete;

        void Print(Level InSeverity, const std::string& InMessage);

        void SetLevel(Level InSeverity);

        template<typename ...Args>
        void Trace(const std::string& InFormatStr, Args&&... InArgs) {
            Print(Level::Trace, Logger::FormatString(InFormatStr, std::forward<Args>(InArgs)...));
        }

        template<typename ...Args>
        void Debug(const std::string& InFormatStr, Args&&... InArgs) {
            Print(Level::Debug, Logger::FormatString(InFormatStr, std::forward<Args>(InArgs)...));
        }

        template<typename ...Args>
        void Info(const std::string& InFormatStr, Args&&... InArgs) {
            Print(Level::Info, Logger::FormatString(InFormatStr, std::forward<Args>(InArgs)...));
        }

        template<typename ...Args>
        void Warning(const std::string& InFormatStr, Args&&... InArgs) {
            Print(Level::Warning, Logger::FormatString(InFormatStr, std::forward<Args>(InArgs)...));
        }

        template<typename ...Args>
        void Error(const std::string& InFormatStr, Args&&... InArgs) {
            Print(Level::Error, Logger::FormatString(InFormatStr, std::forward<Args>(InArgs)...));
        }

        template<typename ...Args>
        void Fatal(const std::string& InFormatStr, Args&&... InArgs) {
            Print(Level::Fatal, Logger::FormatString(InFormatStr, std::forward<Args>(InArgs)...));
        }

    private:
        Logger();

        static std::string FormatStringRecursive(const boost::format& InMessage) {
            return InMessage.str();
        }

        template<typename Type, typename ...Args>
        static std::string FormatStringRecursive(boost::format& InFormatter, Type&& InArg, Args&&... InArgs) {
            InFormatter % std::forward<Type>(InArg);
            return FormatStringRecursive(InFormatter, std::forward<Args>(InArgs)...);
        }


        template<typename ...Args>
        static std::string FormatString(const std::string& InFormatStr, Args&&... InArgs) {
            boost::format Formatter(InFormatStr);
            return FormatStringRecursive(Formatter, std::forward<Args>(InArgs)...);
        }

    private:
        boost::log::sources::severity_logger<boost::log::trivial::severity_level> mImplLogger;
        boost::log::trivial::severity_level mSeverityLevel;
    };
}