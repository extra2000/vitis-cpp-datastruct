#include <boost/format.hpp>
#include <logger.hpp>
#include "engine.hpp"

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::info);
    logcfg.set_min_severity("engine", logger::severity_level::debug);

    myengine::MyEngine my_engine;

    my_engine.set_id(123);

    log.info(boost::format("My Engine ID is '%1%'") % my_engine.get_id());

    return 0;
}
