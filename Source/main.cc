
#include "../Headers/grid.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

int main(int argc,char* argv[]) {
	if (argc < 2) {
		cerr << argv[0] << " <width> <height>" << endl;
		return 1;
	}
	if (argc < 3) {
		cerr << argv[0] << " " << argv[1] << " <height>" << endl;
		return 1;
	}
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);

	cout << "Creating grid of size " << width << "x" << height << "...";
	Utilities::Grid g(width,height);
	cout << "Completed." << endl;

	vector<Path*> paths;
	if (argc > 3) {
		srand(time(NULL));
		int number_paths = atoi(argv[3]);
		cout << "Creating " << number_paths << " paths...";
		for (int i = 0;i < number_paths;i++) {
			Path* new_path = new Path();
			int x = rand() % width;
			int y = rand() % height;
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
	}
	for (unsigned i = 0;i < paths.size();i++) {
		cout << "\tPath " << i+1 << " of " << paths.size() << ": (" 
			 << paths.at(i)->at(0)->get_source().x << "," << paths.at(i)->at(0)->get_source().y << ") ";
		for (unsigned j = 0;j < paths.at(i)->size();j++) {
			cout << "(" << paths.at(i)->at(j)->get_sink().x << "," << paths.at(i)->at(j)->get_sink().y << ") ";
		}
		cout << endl;
		Path* temp = paths.at(i);
		delete temp;
	}
	paths.clear();

	return 0;
}
