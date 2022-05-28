/*
 * engine.hpp
 */

#ifndef INCLUDE_ENGINE_HPP_
#define INCLUDE_ENGINE_HPP_


#include <boost/format.hpp>
#include <logger.hpp>

namespace myengine
{

template < class Tx, class Ty, class Tresult >
class MyEngine
{
protected:
    Tx x;
    Ty y;
    logger::Logger log;
public:
    MyEngine();
    ~MyEngine();
    void set_x(Tx x);
    void set_y(Ty y);
    Tresult compute();
}; // class MyEngine

} // namespace myengine

#include "engine.ipp"


#endif // INCLUDE_ENGINE_HPP_
