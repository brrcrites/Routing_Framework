
#include "../Headers/grid.h"
#include "../Headers/problem_object.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

int main(int argc,char* argv[]) {

	// DO NOT CHANGE THIS SECTION OF CODE
	if(argc < 2) { 
		cout << "Usage: ./grid_router <test_file>" << endl; 
		exit(1);
	}
	Utilities::ProblemObject* first_problem = new Utilities::ProblemObject(std::string(argv[1]));
	// EDIT FROM HERE DOWN

	//Create your problem map object (in our example, we use a simple grid, you should create your own)
	Utilities::Grid g(first_problem->get_width(), first_problem->get_height());

	/*
	Note: we do not take into account the connections or blockers that exist in the Project Object
	You should be accouting for these in your problem map objects (you should not be using Grid). You
	should be using both the Node and Edge classes as the background for whatever problem map object
	you create.
	*/

	/*
	Run your algorithm after creating your problem map object. You should be returning from your algorithm 
	either a Path or a Netlist

	Path: a series of straight line segments, with a single source and a single sink
	Netlist: a series of stright line segments, with a single source and more than one sink
	*/

	//Note, we create random paths just as an example of how to create paths, netlists are created similarly
	vector<Path*> paths;
	srand(time(NULL));
	int number_paths = first_problem->get_connections().size();
	cout << "Creating " << number_paths << " paths...";
	for (int i = 0;i < number_paths;i++) {
		Path* new_path = new Path();
		int x = rand() % first_problem->get_width();
		int y = rand() % first_problem->get_height();
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
	cout << "Completed." << endl;

	//Print the paths/netlists that you return from your algorithm
	for(unsigned i = 0; i < paths.size(); i++) {
		cout << "Path " << i << ": ";
		paths.at(i)->print();
		Path* temp = paths.at(i);
		delete temp;
	}

	paths.clear();

	delete first_problem;

	return 0;
}
