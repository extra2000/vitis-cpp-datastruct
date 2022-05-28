#include <boost/format.hpp>
#include <logger.hpp>
#include "engine.hpp"

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);
    logcfg.set_min_severity("engine", logger::severity_level::debug);

    class myengine::MyEngine< int, int, int > *myengine;
    myengine = new class myengine::MyEngine< int, int, int >();

    myengine->set_x(105);
    myengine->set_y(507);
    int result = myengine->compute();
    log.info(boost::format("Result is %1%") % result);

    delete myengine;

    return 0;
}
