#ifndef EX3_MAP_H
#define EX3_MAP_H
#include <vector>
#include "Point.h"
#include "Grid.h"
#include "GridPt.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/array.hpp>
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
 * this class creates a map of the city for the drivers.
 */
class Map : public Grid {
    private:
        // the max grid size.
        GridPt points[1000][1000];
        Point size;
        vector<Node*>* obstacles;

        friend class boost::serialization::access;
        template<class Archive>
        /**
         * serializes a map.
         * @param ar
         * @param version
         */
        void serialize(Archive &ar, const unsigned int version) {
            ar & boost::serialization::base_object<Grid>(*this);
            ar & size;
            ar & obstacles;
        }
    protected:
        /**
        * fills the grid with points.
        */
        void fillGrid();
    public:
        /**
         * constructs a map.
         * @param size1 the size of the city.
         */
        Map(Point size1);
        /**
         * default contructor to constructs a map.
         */
        Map();
        /**
         * destructs a map.
         */
        ~Map();
        /**
        * checks if a given point is in the grid.
        * @param pt the given point.
        * @return true if the point is in, false otherwise.
        */
        GridPt* getPoint(Point pt);
        /**
         * return a point from the grid.
         * @param pt the point that will be returnd from the grid.
         * @return true if pt is in grid, false otherwise.
         */
        bool isInGrid(Point pt);
        /**
         * sets the neighbors gor a given grid point.
         * @param gp the grid point.
         */
        void neighbors(GridPt* gp);
        /**
        * return a point size of the grid.
        * @return the grid size.
        */
        Point getSize();
        /**
        * initializes the points of the map.
        */
        void initialize();
        /**
         * adds an obstacle to the list.
         * @param obs the new obstacle.
         */
        void addObstacle(Node* obs);
        /**
         * returns the obstacles.
         * @return vector of the obstacles.
         */
        vector<Node*>* getObstacles();
};

#endif //EX3_MAP_H