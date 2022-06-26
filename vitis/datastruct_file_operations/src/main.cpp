#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <logger.hpp>
#include "engine.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    logger::LoggerConfig logcfg;
    logger::Logger log("main");

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("verbose", "sets log level to debug")
        ("cfgfile", po::value<std::string>(), "config filename")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc;
        return 0;
    }

    if (vm.count("verbose"))
    {
        logcfg.set_min_severity("main", logger::severity_level::debug);
        logcfg.set_min_severity("myengine", logger::severity_level::debug);
    }
    else
    {
        logcfg.set_min_severity("main", logger::severity_level::info);
        logcfg.set_min_severity("myengine", logger::severity_level::info);
    }

    myengine::MyEngine myengine;

    if (vm.count("cfgfile"))
    {
        log.debug("Received '--cfgfile' argument");
        log.debug(boost::format("Setting filename to '%1%'") % vm["cfgfile"].as< std::string >());
        myengine.set_filename(vm["cfgfile"].as< std::string >());
    }

    myengine.create_file();

    return 0;
}
