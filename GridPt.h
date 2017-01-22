#ifndef EX3_GRIDPT_H
#define EX3_GRIDPT_H
#include <iostream>
#include <vector>
#include "Node.h"
#include "Point.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
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
/*
 * a class of a grid points. creates a point with special
 * methods only a point on a grid can do. this class inherits from Node.
 */
class GridPt : public Node {
    private:
        Point pt;
        bool passed;
        GridPt* predecessor;
        vector<GridPt*> neighbors;
        int nCounter;
        bool obstacle;

        friend class boost::serialization::access;
        /**
         * seralize a gridPt object.
         * @param ar
         * @param version
         */
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<Node>(*this);
            ar & pt;
            ar & passed;
            ar & predecessor;
            ar & neighbors;
            ar & nCounter;
            ar & obstacle;
        }
    public:
        /**
         * builds a GridPt from a given point.
         * @param pt1 the point we'll build on the grid.
         */
        GridPt(Point pt);
        /**
         * a default constructor for a grid point.
         */
        GridPt();
        /**
         * the distructor of the grid point.
         */
        ~GridPt();
        /**
         * initialize ncounter.
         */
        void initializeCounter();
        /**
         * returns the const point.
         */
        Point getPt() const;
        /**
         * checks if we passed the grid point.
         */
        bool isPassed();
        /**
         * sets if we passed on the point or not.
         */
        void setPassed();
        /**
         *  sets the points predecessor.
         */
        void setPredecessor(Node* pre);
        /**
         *  gets the points predecessor.
         */
        GridPt* getPredecessor();
        /*
         * sets the points neighbors on the grid.
         */
        void setNeighbors(vector<GridPt*>* nb);
        /**
        * checks if the GridPt has a next neighbor.
        * @return true if he does have, false otherwis.
        */
        bool hasNext();
        /**
         * returns the next neighbor.
         */
        GridPt* next();
        /**
         * return either the gridpt is obstacle or not.
         * @return true or false
         */
        bool isObstacle();
        /**
         * sets the bool obstacle of gridpt.
         */
        void setObstacle();
        /**
        * offers the option to use == on grid points(that inherits from Node).
        * @param p1 the node to be compared.
        * @return true if it's the same point, false otherwise.
        */
        bool operator == (const Node &n1) const;
        /**
        * offers the option to use != on grid points(that inherits from Node).
        * @param p1 the node to be compared.
        * @return true if it's not the same point, false otherwise.
        */
        bool operator != (const Node &n1) const;
        /**
          * offers the option to print the GridPt the way we tell him.
          * @param os the stream
          * @param pt1 the point to be printed.
          * @return the way to print the point.
          */
        friend ostream& operator << (ostream& os, const GridPt &pt);
};
#endif //EX3_GRIDPT_H
