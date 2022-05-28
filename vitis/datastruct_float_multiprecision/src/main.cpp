#include <cstddef>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/format.hpp>
#include <logger.hpp>
#include "engine.hpp"

namespace prc = boost::multiprecision;

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");
    logcfg.set_min_severity("main", logger::severity_level::debug);
    logcfg.set_min_severity("engine", logger::severity_level::debug);

    const unsigned int decimal_places = 1000;
    typedef prc::number< prc::cpp_dec_float<decimal_places> > float_prc;

    class myengine::MyEngine< float_prc > *myengine;
    myengine = new class myengine::MyEngine< float_prc >();

    myengine->deposit(float_prc("1000"));
    myengine->deposit(float_prc("1.0e-1000"));
    myengine->deposit(float_prc("1.0e-1000"));
    myengine->withdraw(float_prc("3.0e-1000"));
    myengine->withdraw(float_prc("1.0e-1000"));

    delete myengine;

    return 0;
}
