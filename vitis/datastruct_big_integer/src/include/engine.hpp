/*
 * engine.hpp
 */

#ifndef INCLUDE_ENGINE_HPP_
#define INCLUDE_ENGINE_HPP_


#include <boost/multiprecision/cpp_int.hpp>
#include <boost/format.hpp>
#include <logger.hpp>

namespace myengine
{

template < class T >
class MyEngine
{
protected:
    T result;
    logger::Logger log;
public:
    MyEngine();
    ~MyEngine();
    void compute_factorial(unsigned int max_bitsize);
    T get_result() const;
}; // class MyEngine

} // namespace myengine

#include "engine.ipp"


#endif // INCLUDE_ENGINE_HPP_
