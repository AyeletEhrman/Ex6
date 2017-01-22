#ifndef EX3_GRID_H
#define EX3_GRID_H
#include <iostream>
#include <vector>
#include <deque>
#include "Point.h"
#include "GridPt.h"
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
/*
 * Grid build a an abstract grid of nodes.
 */
class Grid {
    protected:
        /**
        * fills the grid with points.
        */
        virtual void fillGrid() = 0;

        friend class boost::serialization::access;
        /**
        * seralize a grid object.
        * @param ar
        * @param version
        */
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {

        }
    public:
        /**
         * builds the grid with a given size.
         * @param size1 the grid size.
         */
        Grid(Point size);
        /**
        * default constructor for grid;
        */
        Grid();
        /**
         * the distructor of the grid.
         */
        ~Grid();
        /**
         * checks if a given point is in the grid.
         * @param pt the given point.
         * @return true if the point is in, false otherwise.
         */
        virtual GridPt* getPoint(Point pt) = 0;
        /**
         * return a point from the grid.
         * @param pt the point that will be returnd from the grid.
         * @return true if pt is in grid, false otherwise.
         */
        virtual bool isInGrid(Point pt) = 0;
        /**
         * sets the neighbors gor a given grid point.
         * @param gp the grid point.
         */
        virtual void neighbors(GridPt* gp) = 0;
        /**
        * return a point size of the grid.
        * @return the grid size.
        */
        virtual Point getSize() = 0;
        /**
        * initializes the nodes in the grid.
        */
        virtual void initialize() = 0;
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Grid);
#endif //EX3_GRID_H
