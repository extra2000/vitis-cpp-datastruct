/*
 * logger.hpp
 */

#ifndef INCLUDE_LOGGER_HPP_
#define INCLUDE_LOGGER_HPP_


#include <cstddef>
#include <boost/format.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
namespace sinks = boost::log::sinks;

namespace logger {

enum severity_level
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

typedef expr::channel_severity_filter_actor< std::string, severity_level > min_severity_filter;
typedef src::severity_channel_logger< severity_level, std::string > logger_type;
typedef sinks::synchronous_sink< sinks::text_ostream_backend > sink_t;

class LoggerConfig
{
protected:
    boost::shared_ptr< logging::core > m_core;
    boost::shared_ptr< sink_t > m_sink;
    min_severity_filter *m_min_severity;
    void set_formatter();
public:
    LoggerConfig();
    ~LoggerConfig();
    void set_min_severity(const std::string& channel, severity_level level);
};

class Logger
{
protected:
    std::string m_channel;
    logger_type m_log;
    std::string sanitize(const std::string& message);
    void write_log(severity_level level, const std::string& message);
public:
    Logger();
    Logger(const std::string& channel);
    ~Logger();
    void init(const std::string& channel);
    void trace(const std::string& message);
    void trace(const boost::basic_format< char >& format);
    void debug(const std::string& message);
    void debug(const boost::basic_format< char >& format);
    void info(const std::string& message);
    void info(const boost::basic_format< char >& format);
    void warning(const std::string& message);
    void warning(const boost::basic_format< char >& format);
    void error(const std::string& message);
    void error(const boost::basic_format< char >& format);
    void fatal(const std::string& message);
    void fatal(const boost::basic_format< char >& format);
};

std::ostream& operator<< (std::ostream& strm, severity_level level);

} // namespace logger


#endif // INCLUDE_LOGGER_HPP_
