#ifndef _EDGE_BASE_H_
#define _EDGE_BASE_H_

#include "node.h"

/* Note: Edges are undirected */

namespace Utilities {
    class Node;

    class Edge {
        private:
            Node* head;
            Node* tail;

        public:
            /* Constructors/Destructors */
            Edge(Node*, Node*);
            ~Edge();

            /* Accessors */
            Node* get_head();
            Node* get_tail();
            Node* get_end(Node* start);

            /* Mutators */
            void set_head(Node* head);
            void set_tail(Node* tail);
    };
}

#endif  //_EDGE_BASE_H_