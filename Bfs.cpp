#include "Bfs.h"

Bfs::Bfs() {
}

Bfs::~Bfs() {
}

deque<Node*>* Bfs::bfs(Node* current, Node* target) {
    deque<Node*>* nodes = new deque<Node*>();
    // until we find the target.
    while (!(*current == *target)) {
        if (current->hasNext()) {
            Node* next = current->next();
            // if we still did'nt passed this node.
            if (!(next->isPassed())) {
                next->setPassed();
                // we set the predecessor to be the node we came from.
                next->setPredecessor(current);
                // adds the node to the deque.
                nodes->push_back(next);
            }
        } else {
            // no route.
            if (nodes->empty()) {
                cout << "no route" << "\n";
                return nodes;
            } else {
                // current will be the first node in the deque.
                current = nodes->at(0);
                nodes->pop_front();
            }
        }
    }
    delete nodes;
    return finalRoute(current);
}

deque<Node*>* Bfs::finalRoute(Node* current) {
    deque<Node*>* route = new deque<Node*>;
    route->push_front(current);
    // until we get to the starting Node.
    while (current->getPredecessor() != 0) {
        // current will pe now the predecessor.
        current = current->getPredecessor();
        // push's current to the front of the deque.
        route->push_front(current);
    }
    return route;
}
