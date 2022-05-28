/*
 * engine.cpp
 */

#include "engine.hpp"

myengine::MyEngine::MyEngine()
{
    log.init("engine");

    this->id = 0;
    log.debug(boost::format("Initialized Engine with ID = '%1%'") % this->id);
}

myengine::MyEngine::~MyEngine()
{
    log.debug("Engine destroyed");
}

int myengine::MyEngine::get_id() const
{
    return this->id;
}

void myengine::MyEngine::set_id(int id)
{
    log.debug(boost::format("Setting Engine ID to '%1%'") % id);
    this->id = id;
    log.debug(boost::format("Engine ID has been set to '%1%'") % this->id);
}
