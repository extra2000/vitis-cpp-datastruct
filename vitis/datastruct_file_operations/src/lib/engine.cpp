/*
 * engine.cpp
 */

#include <stdexcept>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "engine.hpp"

namespace fs = boost::filesystem;

myengine::MyEngine::MyEngine()
{
    log.init("myengine");

    log.debug("Engine created");

    filename = fs::path("/tmp/datastruct_cpp/default_config.txt");
    log.debug(boost::format("Default config file: '%1%'") % filename);
}

myengine::MyEngine::~MyEngine()
{
    log.debug("Engine destroyed");
}

void myengine::MyEngine::set_filename(const std::string& filename)
{
    log.debug(boost::format("Setting filename to '%1%'") % filename);
    this->filename = fs::path(filename);
    log.debug(boost::format("Filename has been set to %1%") % this->filename);
}

void myengine::MyEngine::create_file()
{
    if (fs::exists(filename))
    {
        log.warning(boost::format("Filename %1% exists. This operation will overwrite the file.") % filename);
        if (fs::is_directory(filename))
        {
            log.error(boost::format("Filename %1% is a directory") % filename);
            throw(std::invalid_argument( (boost::format("Filename %1% should not be a directory") % filename).str() ));
        }
        else
        {
            log.debug(boost::format("Filename %1% is not a directory") % filename);
        }
    }
    else
    {
        log.debug(boost::format("Filename %1% does not exists") % filename);
    }

    this->write_uuid();
}

void myengine::MyEngine::write_uuid()
{
    log.debug(boost::format("Creating %1% for writing") % filename);
    fs::ofstream ofs(filename);

    if (ofs.is_open())
    {
        log.debug(boost::format("Successfully created %1%") % filename);

        std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());
        log.debug(boost::format("Writing '%1%' into %2%") % uuid % filename);
        ofs << uuid << std::endl;
        log.info(boost::format("Successfully written '%1%' into %2%") % uuid % filename);
    }
    else
    {
        log.error(boost::format("Unable to create %1%") % filename);
        throw(std::runtime_error((boost::format("Unable to create %1%") % filename).str()));
    }

    log.debug(boost::format("Closing %1%") % filename);
    ofs.close();
    if (!ofs.is_open())
    {
        log.debug(boost::format("Successfully closed %1%") % filename);
    }
    else
    {
        log.warning(boost::format("Failed to close %1%") % filename);
    }
}

fs::path myengine::MyEngine::get_filename() const
{
    return filename;
}
