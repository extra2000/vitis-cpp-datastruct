/*
 * engine.cpp
 */

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "engine.hpp"

myengine::MyEngine::MyEngine()
{
    log.init("myengine");

    node_root = NULL;
}

myengine::MyEngine::~MyEngine()
{
    log.debug(boost::format("Engine destroyed"));
    if (node_root != NULL)
    {
        log.debug("Destroying nodes");
        delete node_root;
    }
    else
    {
        log.debug("No node to destroy");
    }
}

void myengine::MyEngine::create_node()
{
    log.debug("Creating a new node");
    if (node_root == NULL)
    {
        log.debug("Root node is not yet initialized. Initializing root node");
        node_root = new myengine::node::Node();
    }
    else
    {
        myengine::node::Node *node_leaf = this->get_leaf_node();
        node_leaf->create_next();
    }
}

myengine::node::Node *myengine::MyEngine::get_leaf_node()
{
    log.debug("Searching leaf node");
    myengine::node::Node *node_leaf = node_root;

    log.debug(boost::format("Current node UUID '%1%'") % node_leaf->get_uuid());
    while(node_leaf->get_next() != NULL)
    {
        node_leaf = node_leaf->get_next();
        log.debug(boost::format("Current node UUID '%1%'") % node_leaf->get_uuid());
    }

    log.debug(boost::format("Node UUID '%1%' is the leaf node") % node_leaf->get_uuid());

    return node_leaf;
}

void myengine::MyEngine::list_nodes(node::list_mode list_mode)
{
    switch(list_mode)
    {
    case myengine::node::list_mode::NORMAL:
        break;
    case myengine::node::list_mode::REVERSE:
        break;
    default:
        log.error(boost::format("Invalid list_mode '%1%'") % list_mode);
        throw(std::invalid_argument("Invalid list_mode"));
    }
}

myengine::node::Node::Node()
{
    log.init("myengine.node");

    prev = NULL;
    next = NULL;

    uuid = boost::uuids::to_string(boost::uuids::random_generator()());
    log.info(boost::format("Node created and assign UUID '%1%'") % uuid);
}

myengine::node::Node::~Node()
{
    log.info(boost::format("Node UUID '%1%' destroyed") % uuid);
    if (next != NULL)
    {
        delete next;
    }
    else
    {
        log.debug("There are no more nodes to be destroyed");
    }
}

std::string myengine::node::Node::get_uuid() const
{
    return uuid;
}

myengine::node::Node *myengine::node::Node::get_next() const
{
    return next;
}

myengine::node::Node *myengine::node::Node::get_prev() const
{
    return prev;
}

void myengine::node::Node::create_next()
{
    next = new myengine::node::Node();
    next->prev = this;
}
