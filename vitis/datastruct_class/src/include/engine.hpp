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
    int id;
    logger::Logger log;
public:
    MyEngine();
    ~MyEngine();
    int get_id() const;
    void set_id(int id);
}; // class MyEngine

} // namespace myengine


#endif // INCLUDE_ENGINE_HPP_
