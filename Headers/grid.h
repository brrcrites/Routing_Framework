#ifndef _GRID_BASE_H_
#define _GRID_BASE_H_

#include "node.h"
#include "path.h"
#include "problem_object.h"
#include <vector>

using std::cerr;
using std::endl;
using std::string;
using Utilities::Node;
using Utilities::Edge;
using Utilities::Path;
using Utilities::ProblemObject;

class Grid {
	private:
	    vector<vector<Node*> > grid;
	    int num_connections;
	    vector<Path*> paths;

	public:
	    /* Constructors/Destructors */
	    Grid(ProblemObject* problem_object);
	    ~Grid();

	    /* Accessors */
	    int get_width();
	    int get_height();
	    int get_num_connections();
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

	    /* Algorithms */
	    vector<Path*> test_algorithm();
};

#endif  //_GRID_BASE_H_
