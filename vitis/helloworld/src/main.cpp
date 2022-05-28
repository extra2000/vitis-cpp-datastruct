#include <boost/format.hpp>
#include <logger.hpp>

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::trace);

    log.trace(boost::format("Hello %1%!") % "TRACE");
    log.debug("Hello DEBUG!");
    log.info("Hello INFO!");
    log.warning(R"(\"Hello WARNING!\")");
    log.error(boost::format(R"(Hello \'%1%\'!)") % "ERROR");
    log.fatal("Hello FATAL!");

    return 0;
}
