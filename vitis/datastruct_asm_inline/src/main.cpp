#include <boost/format.hpp>
#include <logger.hpp>

int main()
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);

    int x = 1;
    int y = 0;

    asm(
        "mov %0, %1\n"  // copy x to y
        "add %1, %1, #10"  // x = x + 10
        : "=r" (y)
        : "r" (x)
    );

    log.info(boost::format("y = %1%") % y);

    return 0;
}
