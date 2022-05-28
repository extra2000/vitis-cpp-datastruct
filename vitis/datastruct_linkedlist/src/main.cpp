#include <boost/format.hpp>
#include <logger.hpp>
#include "engine.hpp"

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);
    logcfg.set_min_severity("myengine", logger::severity_level::debug);
    logcfg.set_min_severity("myengine.node", logger::severity_level::debug);

    myengine::MyEngine myengine;

    unsigned int total_nodes = 5;
    log.debug(boost::format("Creating %1% nodes") % total_nodes);
    for (unsigned int i = 0; i < total_nodes; ++i)
    {
        myengine.create_node();
    }

    return 0;
}
