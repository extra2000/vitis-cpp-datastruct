/*
 * engine.cpp
 */

#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <logger.hpp>
#include <engine.hpp>

namespace myengine
{

MyEngine::MyEngine()
{
    log.init("engine");
    log.debug("Engine successfully initialized");
}

MyEngine::~MyEngine()
{
    log.debug("Engine destroyed");
}

void MyEngine::task(unsigned int seconds, const std::string& taskname)
{
    log.debug(boost::format("Taskname '%1%' waiting for %2% seconds") % taskname % seconds);
    boost::this_thread::sleep_for(boost::chrono::seconds(seconds));
    log.debug(boost::format("Taskname '%1%' done waiting for %2% seconds") % taskname % seconds);
}

} // namespace myengine
