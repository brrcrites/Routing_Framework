#include "../Headers/grid.h"
#include "../Headers/edge.h"
#include "../Headers/claim.h"

//Takes an x and y coordinate as input and creates a grid of that size filled with default nodes
Grid::Grid(ProblemObject* problem_object) {
      this->num_connections = problem_object->get_connections().size();
      vector<Blocker> blockers = problem_object->get_blockers();
      int height = problem_object->get_height();
      int width = problem_object->get_width();
      for(int y = 0; y < height; y++) {
	      vector<Node*> temp_row;
	      for(int x = 0; x < width; x++) {
			 Node* new_node;
	      		 //Check to see if what we want to add falls within a blocker, and if it does than don't add it
	      		 bool add_flag = true;
	      		 for(unsigned i = 0; i < blockers.size(); i++) {
			 	  if(x > blockers.at(i).location.x && x <= blockers.at(i).location.x + blockers.at(i).width &&
				  	y > blockers.at(i).location.y && y <= blockers.at(i).location.y + blockers.at(i).height) {
					add_flag = false;
				  }
			  }

			  //If the add flag is true, the node doesn't lie within a blocker and we can add it to the system
			  if(add_flag) {
				  /* 
				  Note that we add connections west and north because we start building in the upper left
				  corner of the system, so as the system fills it links to all the nodes it can connect to
				  that have already been created. This stops the system from accidentally creating multiple
				  connections between two nodes, which could cause issues when routing
				  */
				  new_node = new Node(x,y);
				  if (x > 0) {
				  	  if(temp_row.at(temp_row.size()-1) != NULL) {
						  Edge* west = new Edge(new_node,temp_row.at(temp_row.size()-1));
						  new_node->add_connection(west);
					  }
				  }
				  if (y > 0) {
				          if(grid.at(y-1).at(x) != NULL) {
						  Edge* north = new Edge(new_node,grid.at(y-1).at(x));
						  new_node->add_connection(north);
					  }
				  }
			  }
			  //If the add flag is false, the node shouldn't exist, so we fill its space with a NULL for completeness
			  else {
				new_node = NULL;
			  }
			  temp_row.push_back(new_node);
          }
          this->grid.push_back(temp_row);
      }
}

//Destructs the grid by deleting each node individually, the node destructors will delete their own set of edges
Grid::~Grid() {
      int width = this->get_width();
      int height = this->get_height();
      for(int x = 0; x < height; x++) {
            for(int y = 0; y < width; y++) {
	    	if(grid.at(x).at(y) != NULL) {
                  	delete grid.at(x).at(y);
		  }
            }
      }
}

int Grid::get_width() {
	//Assumes a perfect rectangle
	return grid.empty()?0:grid.at(0).size();
}

int Grid::get_height() {
	//Assumes a perfect rectangle
	return this->grid.size();
}

int Grid::get_num_connections() {
  	return this->num_connections;
}

Node* Grid::get_node(int x, int y) {
      if(y >= this->grid.size()) {
        claim("Attemping to access a node outside of the grid's range (y-value out of range)", Utilities::kError);
	    return NULL;
      }
      else if(x >= this->grid.at(y).size()) {
        claim("Attemping to access a node outside of the grid's range (x-value out of range)", Utilities::kError);
	    return NULL;
      }
      else if(this->grid.at(y).at(x) != NULL) {
      	    return this->grid.at(y).at(x);      //at(...) will throw an out of range exception
      }
      else {
	    return NULL;
      }
}

Node* Grid::get_node(Point coord) {
      return this->get_node(coord.x, coord.y);
}

vector<Path*> Grid::get_paths() {
      return this->paths;
}

Path* Grid::get_path(int i) {
      if(i >= paths.size()) {
            claim("Attempting to access a path outside of the path list's range", Utilities::kError);
      }
      return this->paths.at(i);           //at(...) will throw an out of range exception
}

/*
Since each node has an x/y coordinate, if you pass a Node* into replace node, it will take the node at the passed in
Nodes location, delete it, and then place the passed in node into the grid at its proper location.
*/
void Grid::replace_node(Node* replacement_node) {
      delete this->grid.at(replacement_node->get_y()).at(replacement_node->get_x());
      this->grid.at(replacement_node->get_y()).at(replacement_node->get_x()) = replacement_node;
}

void Grid::set_paths(vector<Path*> paths) {
      this->paths = paths;
}

void Grid::add_path(Path* path) {
      this->paths.push_back(path);
}

void Grid::replace_path(int i, Path* path) {
      if(i >= this->paths.size()) {
            claim("Attemping to replace path outside of the path list's range", Utilities::kError);
      }
      paths.at(i) = path;
}

void Grid::remove_path(int i) {
      if(i >= paths.size()) {
      	claim("Attempting to remove a path outside of the path list's range", Utilities::kError);
      }
      vector<Path*>::iterator it = this->paths.begin();
      it += i;
      paths.erase(it);
}

//Note, we create random paths just as an example of how to create paths, netlists are created similarly
vector<Path*> Grid::test_algorithm() {
    vector<Path*> paths;
    srand(time(NULL));
    int number_paths = this->get_num_connections();
    for (int i = 0;i < number_paths;i++) {
      Path* new_path = new Path();
      int x = rand() % this->get_width();
      int y = rand() % this->get_height();
      int path_length = 1+rand()%10;
      for (unsigned j = 0;j < path_length;j++) {
        bool direction = rand()%2;
        Point head(x,y);
        direction?x+=1:y+=1;
        Point tail(x,y);
        PathSegment* new_segment = new PathSegment(head,tail);
        new_path->add_segment(new_segment);
      }
      paths.push_back(new_path);
    }
    return paths;
}
