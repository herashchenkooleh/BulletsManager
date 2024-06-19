#include "bm/Logger.hpp"

#include <boost/log/common.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/expressions.hpp>
#include <fstream>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>
#include <iostream>

namespace bm {
    /*static*/ Logger& Logger::GetInstance() {
        static Logger sInstance;
        return sInstance;
    }

    Logger::Logger()
        : mSeverityLevel(boost::log::trivial::severity_level::debug) {
        boost::shared_ptr< boost::log::core > core = boost::log::core::get();

        boost::shared_ptr<boost::log::sinks::text_ostream_backend > backend = boost::make_shared< boost::log::sinks::text_ostream_backend>();
        backend->add_stream(boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter()));
        backend->add_stream(boost::shared_ptr<std::ostream>(new std::ofstream("BulletManager.log")));

        backend->auto_flush(true);

        typedef  boost::log::sinks::synchronous_sink< boost::log::sinks::text_ostream_backend> sink_t;
        boost::shared_ptr<sink_t> sink(new sink_t(backend));

        sink->set_filter(boost::log::trivial::severity >= mSeverityLevel);

        sink->set_formatter
        (
            boost::log::expressions::format("[%1%][%2%]: %3%")
            % boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
            % boost::log::trivial::severity
            % boost::log::expressions::smessage
        );


        core->add_sink(sink);
        boost::log::add_common_attributes();
    }

    void Logger::Print(Level InSeverity, const std::string& InMessage) {
        switch (InSeverity)
        {
            case Logger::Level::Trace:
                BOOST_LOG_SEV(mImplLogger, boost::log::trivial::trace) << InMessage;
            break;
            case Logger::Level::Debug:
                BOOST_LOG_SEV(mImplLogger, boost::log::trivial::debug) << InMessage;
            break;
            case Logger::Level::Info:
                BOOST_LOG_SEV(mImplLogger, boost::log::trivial::info) << InMessage;
            break;
            case Logger::Level::Warning:
                BOOST_LOG_SEV(mImplLogger, boost::log::trivial::warning) << InMessage;
            break;
            case Logger::Level::Error:
                BOOST_LOG_SEV(mImplLogger, boost::log::trivial::error) << InMessage;
            break;
            case Logger::Level::Fatal:
                BOOST_LOG_SEV(mImplLogger, boost::log::trivial::fatal) << InMessage;
            break;
            default:
                break;
        }
    }

    void Logger::SetLevel(Level InSeverity) {
        switch (InSeverity) {
            case Level::Trace: {
                mSeverityLevel = boost::log::trivial::severity_level::trace;
                break;
            }
            case Level::Debug: {
                mSeverityLevel = boost::log::trivial::severity_level::debug;
                break;
            }
            case Level::Info: {
                mSeverityLevel = boost::log::trivial::severity_level::info;
                break;
            }
            case Level::Warning: {
                mSeverityLevel = boost::log::trivial::severity_level::warning;
                break;
            }
            case Level::Error: {
                mSeverityLevel = boost::log::trivial::severity_level::error;
                break;
            }
            case Level::Fatal: {
                mSeverityLevel = boost::log::trivial::severity_level::fatal;
                break;
            }
        }
    }
}