/*
 * engine.hpp
 */

#ifndef INCLUDE_ENGINE_HPP_
#define INCLUDE_ENGINE_HPP_


// Prevent old features, as recommended by Boost documentations
#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <logger.hpp>

namespace myengine
{

class MyEngine
{
protected:
    logger::Logger log;
    boost::filesystem::path filename;
    void write_uuid();
public:
    MyEngine();
    ~MyEngine();
    void set_filename(const std::string& filename);
    boost::filesystem::path get_filename() const;
    void create_file();
}; // class MyEngine

} // namespace myengine


 #endif // INCLUDE_ENGINE_HPP_
