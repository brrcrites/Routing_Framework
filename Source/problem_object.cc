#include "../Headers/problem_object.h"
#include "../Headers/claim.h"

Utilities::ProblemObject::ProblemObject() {
	this->name = "";
	this->width = 0;
	this->height = 0;
}

Utilities::ProblemObject::ProblemObject(string filename) {
	//Create a new JSON file object and parse the file given
	JSON::JsonFile* json_file = new JSON::JsonFile();
	json_parse(filename,json_file);

	//Check that there is at least one object, otherwise there is nothing to do (malformed JSON)
	if(json_file->objects_size() < 1) {
		claim("The JSON parser failed because the file input has no objects",kError);
	}

	//We expect there to be one object, so we want to get that object
	JSON::JsonObject* file_object = json_file->objects_at(0);

	//First we extract the name, which requires looking for the name tag
	JsonValue* problem_name = file_object->find("name");
	//First we check that we got a return from teh call to find("name")
	if(problem_name) {
		//If we did get a return, then we want to check that what we got was a string
		if(problem_name->is_string()) {
			//If it is a string, then we want to extract the value as a string and assign it
			this->name = problem_name->get_string();
		}
	} else {
		//Otherwise, we just assign an empty string
		this->name = "";
	}

	//Extract the width and the height of the problem as integers
	this->height = extract_int(file_object->find("height"));
	this->width = extract_int(file_object->find("width"));

	/*
	Now we want to get the list of blockers (squares in the grid that are invalid for routing), however since
	there are many of these in one problem, we represent them in the JSON object as an array
	*/
	JsonValue* list = file_object->find("blockerList");
	//We have to make sure that this list is an array, otherwise we have a malformed JSON object
	if(list && list->is_array()) {
		JsonArray* array = list->get_array();
		if(array->size() <= 0) {
			claim("There are no blockers in this system, this is possible but unusual",kWarning);
		} else {
			/*
			We now know this is a JSON array, so we need to iterate through it, check that each part is an
			object (if not, its some bit of malformed JSON object), and then add the blocker
			*/
			for(unsigned i = 0; i < array->size(); i++) {
				JsonValue* current_value = array->at(i);
				if(current_value->is_object()) {
					add_blocker(current_value->get_object());
				}
			}
		}
	}

	//Now we do the same as above, but for the list of routes that we need to solve
	list = file_object->find("routeList");
	if(list && list->is_array()) {
		JsonArray* array = list->get_array();
		if(array->size() <= 0) {
			claim("There are no routes in this system, this is possible but unusual",kWarning);
		} else {
			for(unsigned i = 0; i < array->size(); i++) {
				JsonValue* current_value = array->at(i);
				if(current_value->is_object()) {
					add_connection(current_value->get_object());
				}
			}
		}
	}

	delete json_file;
	//And now were done with a fully formed problem
}

Utilities::ProblemObject::~ProblemObject() {
	/* Empty Destructor */
}

void Utilities::ProblemObject::add_blocker(JsonObject* blocker) {
	Blocker new_blocker;
	JsonValue* blocker_name = blocker->find("name");
	if(blocker_name && blocker_name->is_string()) {
		new_blocker.name = blocker_name->get_string();
	} else {
		claim("Blocker does not have a name, likely malformed JSON file",kWarning);
	}
	new_blocker.width = extract_int(blocker->find("width"));
	new_blocker.height = extract_int(blocker->find("height"));
	new_blocker.location.x = extract_int(blocker->find("x"));
	new_blocker.location.y = extract_int(blocker->find("y"));
	this->blockers.push_back(new_blocker);
}

void Utilities::ProblemObject::add_connection(JsonObject* connection) {
	Connection new_connection;
	JsonValue* connection_name = connection->find("name");
	if(connection_name && connection_name->is_string()) {
		new_connection.name = connection_name->get_string();
	} else {
		claim("Connection does not have a name, likely malformed JSON file",kWarning);
	}
	new_connection.source.x = extract_int(connection->find("source_x"));
	new_connection.source.y = extract_int(connection->find("source_y"));
	new_connection.sink.x = extract_int(connection->find("sink_x"));
	new_connection.sink.y = extract_int(connection->find("sink_y"));
	this->connections.push_back(new_connection);
}

int Utilities::ProblemObject::extract_int(JsonValue* int_value) {
	if (int_value != NULL) {
		if (int_value->is_int()) {
			return int_value->get_int();
		}
	}
	return 0;
}