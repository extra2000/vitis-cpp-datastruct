/*
 * engine.hpp
 */

#ifndef INCLUDE_ENGINE_HPP_
#define INCLUDE_ENGINE_HPP_


#include <logger.hpp>


namespace myengine
{

class MyEngine
{
protected:
    logger::Logger log;
public:
    MyEngine();
    ~MyEngine();
    void task(unsigned int seconds, const std::string& taskname);
}; // class MyEngine

} // myengine


#endif // INCLUDE_ENGINE_HPP_
