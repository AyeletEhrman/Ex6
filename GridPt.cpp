#include "GridPt.h"
using namespace std;

GridPt::GridPt(Point pt1) : Node() {
    pt = pt1;
    passed = false;
    predecessor = NULL;
    nCounter = 0;
    obstacle = false;
}

GridPt::GridPt() : Node() {
}

GridPt::~GridPt() {
}

void GridPt::initializeCounter() {
    nCounter = 0;
}

Point GridPt::getPt() const {
    return pt;
}

bool GridPt::isPassed() {
    return passed;
}

void GridPt::setPassed() {
    passed = !isPassed();
}

void GridPt::setPredecessor(Node* pre) {
    predecessor = (GridPt*)pre;
}

GridPt* GridPt::getPredecessor() {
    return predecessor;
}

void GridPt::setNeighbors(vector<GridPt*>* nb) {
    neighbors = *nb;
}

bool GridPt::hasNext() {
    return (nCounter < neighbors.size());
}

GridPt* GridPt::next() {
    nCounter++;
    return neighbors.at(nCounter - 1);
}

bool GridPt::isObstacle() {
    return obstacle;
}

void GridPt::setObstacle() {
    obstacle = !obstacle;
}


bool GridPt::operator == (const Node &p1) const {
    return ((pt.getX() == (((const GridPt&)p1).getPt().getX())
             && (pt.getY() == ((const GridPt&)p1).getPt().getY())));
}
bool GridPt::operator != (const Node &p1) const {
    return ((pt.getX() != (((const GridPt&)p1).getPt().getX())
             || (pt.getY() != ((const GridPt&)p1).getPt().getY())));
}

ostream& operator << (ostream& os, const GridPt &pt1) {
    // will print like that: (x,y).
    return os << "(" << pt1.getPt().getX() << "," << pt1.getPt().getY() << ")";
}

