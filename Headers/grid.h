#ifndef _GRID_BASE_H_
#define _GRID_BASE_H_

#include "node.h"
#include "path.h"
#include <vector>

using std::cerr;
using std::endl;
using std::string;
using Utilities::Node;
using Utilities::Path;

namespace Utilities {
    class Grid {
        private:
            vector<vector<Node*> > grid;
            vector<Path*> paths;

        public:
            /* Constructors/Destructors */
            Grid(int width, int height);
            ~Grid();

            /* Accessors */
            int get_width();
            int get_height();
            Node* get_node(int x, int y);
            Node* get_node(Point coord);
            vector<Path*> get_paths();
            Path* get_path(int i);

            /* Mutators */
            void replace_node(Node* replacement_node);
            void set_paths(vector<Path*> paths);
            void add_path(Path* path);
            void replace_path(int i, Path* path);
            void remove_path(int i);
    };
}

#endif  //_GRID_BASE_H_
