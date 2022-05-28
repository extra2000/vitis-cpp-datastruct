#include <boost/multiprecision/cpp_int.hpp>
#include <boost/format.hpp>
#include <logger.hpp>
#include "engine.hpp"

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);
    logcfg.set_min_severity("engine", logger::severity_level::debug);

    class myengine::MyEngine< boost::multiprecision::cpp_int > *myengine;
    myengine = new class myengine::MyEngine< boost::multiprecision::cpp_int >();

    unsigned int bitsize = 8192;
    myengine->compute_factorial(bitsize);
    boost::multiprecision::cpp_int result = myengine->get_result();

    delete myengine;

    log.info(boost::format("The largest factorial for %1% integer is %2%") % bitsize % result);

    return 0;
}
