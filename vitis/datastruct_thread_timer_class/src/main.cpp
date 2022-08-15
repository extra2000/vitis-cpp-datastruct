#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <logger.hpp>
#include <engine.hpp>

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);
    logcfg.set_min_severity("engine", logger::severity_level::debug);

    myengine::MyEngine *engine = new myengine::MyEngine();

    log.debug("Running tasks synchronously");
    engine->task(7, "J-001");
    engine->task(5, "J-002");

    log.debug("Running tasks asynchronously via threads");
    boost::thread_group threads;
    threads.create_thread(boost::bind(&myengine::MyEngine::task, engine, 7, "J-001"));
    threads.create_thread(boost::bind(&myengine::MyEngine::task, engine, 5, "J-002"));

    log.debug("Waiting for all threads to complete");
    threads.join_all();

    log.debug("All threads completed. Exiting the program ...");

    delete engine;

    return 0;
}
