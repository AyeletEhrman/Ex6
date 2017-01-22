#ifndef EX3_BFS_H
#define EX3_BFS_H
#include <iostream>
#include <deque>
#include "Node.h"
#include "GridPt.h"
using namespace std;
/*
 * this class will find the best route from one point to another
 * using the BFS algorithm
 */
class Bfs {
    private:
       /**
       * creates a deque of the route and returns it.
       * @param current the last node in the route.
       * @return a deque of the route.
       */
        deque<Node*>* finalRoute(Node *current);
    public:
        /**
         * constructs a Bfs.
         */
        Bfs();
        /**
         * disstructs a Bfs.
         */
        ~Bfs();
        /**
         * this func finds a route with the bfs algorithm.
         * @param current the starting node.
         * @param target the ending node.
         * @return a deque of the final route.
         */
        deque<Node*>* bfs(Node *current, Node *target);
};

#endif //EX3_BFS_H