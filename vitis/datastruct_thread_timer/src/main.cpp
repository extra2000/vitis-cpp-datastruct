#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <logger.hpp>

void wait(int seconds, logger::Logger& log)
{
    log.debug(boost::format("Waiting for %1% seconds") % seconds);
    boost::this_thread::sleep_for(boost::chrono::seconds(seconds));
    log.debug(boost::format("Done waiting for %1% seconds") % seconds);
}

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);

    log.debug("Spawning threads");
    boost::thread_group threads;
    threads.create_thread(boost::bind(wait, 7, log));
    threads.create_thread(boost::bind(wait, 5, log));
    threads.create_thread(boost::bind(wait, 2, log));
    threads.create_thread(boost::bind(wait, 9, log));

    log.debug("Waiting all threads to complete");
    threads.join_all();

    log.debug("All threads completed. Exiting the program ...");

    return 0;
}
