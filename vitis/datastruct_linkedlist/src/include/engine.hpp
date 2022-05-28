/*
 * engine.hpp
 */

#ifndef INCLUDE_ENGINE_HPP_
#define INCLUDE_ENGINE_HPP_


#include <logger.hpp>

namespace myengine
{

namespace node
{

enum list_mode
{
    NORMAL,
    REVERSE
};

class Node
{
protected:
    logger::Logger log;
    std::string uuid;
    Node *prev;
    Node *next;
public:
    Node();
    ~Node();
    std::string get_uuid() const;
    Node *get_next() const;
    Node *get_prev() const;
    void create_next();
}; // class Node

} // namespace node

class MyEngine
{
protected:
    logger::Logger log;
    node::Node *node_root;
    node::Node *get_leaf_node();
public:
    MyEngine();
    ~MyEngine();
    void create_node();
    void list_nodes(node::list_mode list_mode);
}; // class MyEngine

} // namespace myengine


#endif // INCLUDE_ENGINE_HPP_
