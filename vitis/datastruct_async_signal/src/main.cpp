#include <string>
#include <boost/format.hpp>
#include <boost/signals2.hpp>
#include <boost/bind/bind.hpp>
#include <logger.hpp>

void printer_01(logger::Logger& log, const std::string& msg)
{
    log.info(boost::format("<< Printer 01 >> %1%") % msg);
}

void printer_02(logger::Logger& log, const std::string& msg)
{
    log.info(boost::format("<< Printer 02 >> %1%") % msg);
}

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);

    boost::signals2::signal< void() > sig;
    sig.connect(boost::bind(printer_01, log, "Hello Signals2!!!"));
    sig.connect(boost::bind(printer_02, log, "Hello Signals2***"));

    sig();

    return 0;
}
