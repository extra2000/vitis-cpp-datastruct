#include <vector>
#include <boost/format.hpp>
#include <logger.hpp>

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::trace);

    std::vector< int > counter_queue;

    // Insert 3 & 5 into queue
    counter_queue.push_back(3);
    counter_queue.push_back(5);

    // Insert 4 after 3 (which is at 2nd position)
    counter_queue.insert(counter_queue.begin()+1, 4);

    // Insert 1 at the beginning
    counter_queue.insert(counter_queue.begin(), 1);

    // Insert 2 after 1 (which is at 2nd position)
    counter_queue.insert(counter_queue.begin()+1, 2);

    // Alternative way to insert 6 at the end
    counter_queue.insert(counter_queue.end(), 6);

    for (auto customer_number : counter_queue)
    {
        log.info(boost::format("%d") % customer_number);
    }

    return 0;
}
