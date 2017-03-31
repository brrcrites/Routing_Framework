#include "../Headers/problem_object.h"
#include "../Headers/claim.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::cerr;
using std::endl;
using std::fstream;

Utilities::ProblemObject::ProblemObject() {
	this->name = "";
	this->width = 0;
	this->height = 0;
}

Utilities::ProblemObject::ProblemObject(string filename) {

	//Create a new JSON file object and parse the file given
	fstream input_file;
	input_file.open(filename);
	if(!input_file.is_open()) {
		cerr << "Unable to open input file, failing..." << endl;
		exit(-1);
	}

	//Check that there is at least one object, otherwise there is nothing to do (malformed JSON)
	string file, line;
	while(getline(input_file, line)) {
		file += line;
	}
	input_file.close();

	//We expect there to be one object, so we want to get that object
	json json_file = json::parse(file);

	//First we extract the name, which requires looking for the name tag
	if(json_file.find("name") != json_file.end()) {
		this->name = json_file.at("name");
	} else {
		cout << "No name was provided in the input file, renaming it " << filename << endl;
		this->name = filename;
	}

	//Then we check that we got a return from teh call to find("name")
	if(json_file.find("height") == json_file.end()) {
		cerr << "No height was provided in the input file, failing..." << endl;
		exit(-1);
	}
	if(json_file.find("width") == json_file.end()) {
		cerr << "No width was provided in the input file, failing..." << endl;
		exit(-1);
	}
	this->height = json_file.at("height");
	this->width = json_file.at("width");

	//Now we want to get the list of blockers (squares in the grid that are invalid for routing), however since
	//there are many of these in one problem, we represent them in the JSON object as an array
	if(json_file.find("blockerList") == json_file.end()) {
		cout << "No blockers were specified in the input file" << endl;
	} else {
		if(!json_file.at("blockerList").is_array()) {
			cerr << "The \"blockerList\" in the input file must be an array, failing..." << endl;
			exit(-1);
		}
		for(unsigned i = 0; i < json_file.at("blockerList").size(); i++) {
			add_blocker(json_file.at("blockerList").at(i));
		}
	}

	//Now we do the same as above, but for the list of routes that we need to solve
	if(json_file.find("routeList") == json_file.end()) {
		cout << "No routes were specified in the input file" << endl;
	} else {
		if(!json_file.at("routeList").is_array()) {
			cerr << "The \"routeList\" in the input file must be an array, failing..." << endl;
			exit(-1);
		}
		for(unsigned i = 0; i < json_file.at("routeList").size(); i++) {
			add_connection(json_file.at("routeList").at(i));
		}
	}
}

Utilities::ProblemObject::~ProblemObject() {
	/* Empty Destructor */
}

void Utilities::ProblemObject::add_blocker(json blocker) {

	Blocker new_blocker;

	if(blocker.find("name") == blocker.end()) {
		cout << "A blocker was defined in the input file with no name, renaming it blocker" << this->blockers.size() << endl;
		new_blocker.name = "blocker" + std::to_string(this->blockers.size());
	} else {
		new_blocker.name = blocker.at("name");
	}

	if(blocker.find("height") == blocker.end()) {
		cerr << "Blocker " << new_blocker.name << " was defined without a height, failing..." << endl;
		exit(-1);
	}
	if(blocker.find("width") == blocker.end()) {
		cerr << "Blocker " << new_blocker.name << " was defined without a width, failing..." << endl;
		exit(-1);
	}
	if(blocker.find("x") == blocker.end()) {
		cerr << "Blocker " << new_blocker.name << " was defined without a x position, failing..." << endl;
		exit(-1);
	}
	if(blocker.find("y") == blocker.end()) {
		cerr << "Blocker " << new_blocker.name << " was defined without a y position, failing..." << endl;
		exit(-1);
	}

	new_blocker.height = blocker.at("height");
	new_blocker.width = blocker.at("width");
	new_blocker.location.x = blocker.at("x");
	new_blocker.location.y = blocker.at("y");

	this->blockers.push_back(new_blocker);
}

void Utilities::ProblemObject::add_connection(json connection) {
	Connection new_connection;

	if(connection.find("name") == connection.end()) {
		cout << "A connection was defined in the input file with no name, renaming it connection" << this->connections.size() << endl;
		new_connection.name = "connection" + std::to_string(this->connections.size());
	} else {
		new_connection.name = connection.at("name");
	}

	if(connection.find("source_x") == connection.end()) {
		cerr << "Connection " << new_connection.name << " was defined withou a source_x position, failing..." << endl;
		exit(-1);
	}
	if(connection.find("source_y") == connection.end()) {
		cerr << "Connection " << new_connection.name << " was defined withou a source_y position, failing..." << endl;
		exit(-1);
	}
	if(connection.find("sink_x") == connection.end()) {
		cerr << "Connection " << new_connection.name << " was defined withou a sink_x position, failing..." << endl;
		exit(-1);
	}
	if(connection.find("sink_y") == connection.end()) {
		cerr << "Connection " << new_connection.name << " was defined withou a sink_y position, failing..." << endl;
		exit(-1);
	}

	new_connection.source.x = connection.at("source_x");
	new_connection.source.y = connection.at("source_y");
	new_connection.sink.x = connection.at("sink_x");
	new_connection.sink.y = connection.at("sink_y");

	this->connections.push_back(new_connection);
}

