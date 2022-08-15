#include <boost/format.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <logger.hpp>

void counter(
    const boost::system::error_code& /*e*/,
    boost::asio::steady_timer *t,
    unsigned int *count,
    unsigned int seconds,
    const std::string& countername,
    logger::Logger& log)
{
    if (*count < seconds)
    {
        ++(*count);
        log.debug(boost::format("Counter '%1%' elapsed is %2% seconds until %3% seconds") % countername % *count % seconds);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(boost::bind(counter, boost::asio::placeholders::error, t, count, seconds, countername, log));
    }
    else
    {
        log.debug(boost::format("Counter '%1%' finished counting") % countername);
    }
}

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);

    boost::asio::io_context io;
    boost::asio::steady_timer cnt_timer1(io, boost::asio::chrono::seconds(0));
    boost::asio::steady_timer cnt_timer2(io, boost::asio::chrono::seconds(0));
    unsigned int count1 = 0;
    unsigned int count2 = 0;

    cnt_timer1.async_wait(boost::bind(counter, boost::asio::placeholders::error, &cnt_timer1, &count1, 5, "C001", log));
    cnt_timer2.async_wait(boost::bind(counter, boost::asio::placeholders::error, &cnt_timer2, &count2, 3, "C002", log));

    log.debug("Waiting for all tasks to complete ...");
    io.run();

    log.debug("All task completed, exiting proram");

    return 0;
}
