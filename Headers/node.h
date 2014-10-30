#ifndef _NODE_BASE_H_
#define _NODE_BASE_H_

#include "../Headers/point.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cerr;
using std::endl;

namespace Utilities {
    class Edge;

    class Node {
        private:
            Point coord;
            vector<Edge*> connections;
            int cost;

            /* Private Mutators */
            void add_connection_mirrored(Edge*);

        public:
            /* Constructors/Destructors */
            Node(int x, int y, int cost=0);
            Node(Point coord, int cost=0);
            ~Node();

            /* Accessors */
            Point get_coord();
            int get_x();
            int get_y();
	        unsigned connections_size();
            bool connections_empty();
            bool connections_contains(Edge* edge);
	        Edge* connections_at(unsigned index);
            int get_cost();

            /* Mutators */
            void set_coord(int x, int y);
            void set_x_coord(int x);
            void set_y_coord(int y);
            void set_coord(Point coord);
            void set_connections(vector<Edge*> connections);
            void add_connection(Edge* connection);
            void set_cost(int cost);
            void remove_connection(Edge* connection);
    };
}

#endif  //_NODE_BASE_H_
