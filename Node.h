#ifndef EX3_NODE_H
#define EX3_NODE_H
#include <iostream>
#include "Point.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
using namespace std;
using namespace boost::archive;

/**
 * this class creates an abstract class of a node.
 * each class that will inherit from Node will implement the following funcs.
 */
class Node {
    private:
        friend class boost::serialization::access;
        /**
         * serializes a node.
         * @param ar
         * @param version
         */
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {

        }
    public:
        /**
         * constructs a Node.
         */
        Node();
        /**
         * destructs a Node.
         */
        ~Node();
        /**
        * checks if the GridPt has a next node.
        * @return true if he does have, false otherwis.
        */
        virtual bool hasNext() = 0;
        /**
         * returns the next node.
         */
        virtual Node* next() = 0;
        /**
         * checks if we passed the node.
         */
        virtual bool isPassed() = 0;
        /**
         * sets if we passed on the node or not.
         */
        virtual void setPassed() = 0;
        /**
         *  sets the nodes predecessor.
         */
        virtual void setPredecessor(Node* current) = 0;
        /**
         *  gets the nodes predecessor.
         */
        virtual Node* getPredecessor() = 0;
        /**
         * offers the option to use == on grid points(that inherits from Node).
         * @param n1 the node to be compared.
         * @return true if it's the same node, false otherwise.
         */
        virtual bool operator == (const Node &n1) const = 0;
        /**
         * offers the option to use != on grid points(that inherits from Node).
         * @param n1 the node to be compared.
         * @return false if it's the same node, true otherwise.
         */
        virtual bool operator != (const Node &n1) const = 0;
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Node);
#endif //EX3_NODE_H