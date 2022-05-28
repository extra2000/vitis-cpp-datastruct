/*
 * engine.hpp
 */

#ifndef INCLUDE_ENGINE_HPP_
#define INCLUDE_ENGINE_HPP_


#include <stdexcept>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/format.hpp>
#include <logger.hpp>

namespace myengine
{

template < class T >
class MyEngine
{
protected:
    T saving;
    logger::Logger log;
public:
    MyEngine();
    ~MyEngine();
    void deposit(T amount);
    void withdraw(T amount);
}; // class MyEngine

} // namespace myengine

#include "engine.ipp"


#endif // INCLUDE_ENGINE_HPP_
