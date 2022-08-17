/*
 * logger.cpp
 */

#include "logger.hpp"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
namespace sinks = boost::log::sinks;

BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(process_id, "ProcessID", attrs::current_process_id::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(thread_id, "ThreadID", attrs::current_thread_id::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", logger::severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(channel, "Channel", std::string)

DllExport logger::LoggerConfig::LoggerConfig()
{
    logging::add_common_attributes();

    m_core = logging::core::get();

    m_min_severity = new min_severity_filter(expr::channel_severity_filter(channel, severity));

    boost::shared_ptr< sinks::text_ostream_backend > backend = boost::make_shared< sinks::text_ostream_backend >();
    backend->add_stream(boost::shared_ptr< std::ostream >(&std::clog, boost::null_deleter()));

    m_sink = boost::shared_ptr< sink_t >(new sink_t(backend));
    m_core->add_sink(m_sink);

    this->set_formatter();
}

DllExport logger::LoggerConfig::~LoggerConfig()
{
    delete m_min_severity;
}

void logger::LoggerConfig::set_formatter()
{
    logging::formatter formatter = expr::format("{\"timestamp\": \"%1%\", \"process_id\": \"%2%\", \"thread_id\": \"%3%\", \"channel\": \"%4%\", \"severity\": \"%5%\", \"message\": \"%6%\"}")
        % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
        % expr::attr< attrs::current_process_id::value_type >("ProcessID")
        % expr::attr< attrs::current_thread_id::value_type >("ThreadID")
        % expr::attr< std::string >("Channel")
        % expr::attr< severity_level >("Severity")
        % expr::smessage;

    m_sink->set_formatter(formatter);
}

DllExport void logger::LoggerConfig::set_min_severity(const std::string& channel, logger::severity_level level)
{
    // Add minimum severity for a channel
    (*m_min_severity)[channel] = level;

    // Set minimum severity for the channel and minimum fatal by default
    m_sink->set_filter((*m_min_severity) | (severity >= logger::severity_level::fatal));
}

DllExport logger::Logger::Logger()
{
}

DllExport logger::Logger::Logger(const std::string& channel)
{
    this->init(channel);
}

DllExport logger::Logger::~Logger()
{
}

DllExport void logger::Logger::init(const std::string& channel)
{
    m_channel = channel;
    m_log = logger::logger_type(keywords::channel = m_channel);
}

std::string logger::Logger::sanitize(const std::string& message)
{
    std::string msg = message;
    boost::replace_all(msg, "\"", "'");

    return msg;
}

void logger::Logger::write_log(logger::severity_level level, const std::string& message)
{
    logging::record rec = m_log.open_record(keywords::severity = level);
    if (rec)
    {
        logging::record_ostream strm(rec);
        strm << message;
        strm.flush();
        m_log.push_record(boost::move(rec));
    }
}

DllExport void logger::Logger::trace(const std::string& message)
{
    this->write_log(logger::severity_level::trace, this->sanitize(message));
}

DllExport void logger::Logger::trace(const boost::basic_format< char >& format)
{
    this->write_log(logger::severity_level::trace, this->sanitize(format.str()));
}

DllExport void logger::Logger::debug(const std::string& message)
{
    this->write_log(logger::severity_level::debug, this->sanitize(message));
}

DllExport void logger::Logger::debug(const boost::basic_format< char >& format)
{
    this->write_log(logger::severity_level::debug, this->sanitize(format.str()));
}

DllExport void logger::Logger::info(const std::string& message)
{
    this->write_log(logger::severity_level::info, this->sanitize(message));
}

DllExport void logger::Logger::info(const boost::basic_format< char >& format)
{
    this->write_log(logger::severity_level::info, this->sanitize(format.str()));
}

DllExport void logger::Logger::warning(const std::string& message)
{
    this->write_log(logger::severity_level::warning, this->sanitize(message));
}

DllExport void logger::Logger::warning(const boost::basic_format< char >& format)
{
    this->write_log(logger::severity_level::warning, this->sanitize(format.str()));
}

DllExport void logger::Logger::error(const std::string& message)
{
    this->write_log(logger::severity_level::error, this->sanitize(message));
}

DllExport void logger::Logger::error(const boost::basic_format< char >& format)
{
    this->write_log(logger::severity_level::error, this->sanitize(format.str()));
}

DllExport void logger::Logger::fatal(const std::string& message)
{
    this->write_log(logger::severity_level::fatal, this->sanitize(message));
}

DllExport void logger::Logger::fatal(const boost::basic_format< char >& format)
{
    this->write_log(logger::severity_level::fatal, this->sanitize(format.str()));
}

std::ostream& logger::operator<< (std::ostream& strm, logger::severity_level level)
{
    static const char* strings[] =
    {
        "trace",
        "debug",
        "info",
        "warning",
        "error",
        "fatal"
    };

    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
    {
        strm << strings[level];
    }
    else
    {
        strm << static_cast< int >(level);
    }

    return strm;
}
