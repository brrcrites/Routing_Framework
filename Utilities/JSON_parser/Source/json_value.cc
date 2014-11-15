
#include "json_value.h"

string JSON::type_string(kJsonType type) { 
	switch (type) {
		case kString: 
			return "String";
		case kInt:
			return "Int";
		case kFloat:
			return "Float";
		case kBool:
			return "Bool";
		case kObject:
			return "Object";
		case kArray:
			return "Array";
		case kNull:
			return "Null";
		default:
			return "None";
	}
}

JSON::JsonValue::~JsonValue() {
	if (is_string()) { 
		delete(value.string_value);
	} else if (is_object()) {
		//delete(value.object);
	} else if (is_array()) {
		//delete(value.array);
	}
}

int JSON::JsonValue::size_of() {
	switch (type) {
		case kString:
			return sizeof(value.string_value);
		case kInt:
			return sizeof(int);
		case kFloat:
			return sizeof(float);
		case kBool:
			return sizeof(bool);
		case kNull:
			return sizeof(value.null);
		default:
			return 0;
	}
}

string JSON::JsonValue::get_string() { 
	if (is_string()) { return *value.string_value; } 
	return "";
}

int JSON::JsonValue::get_int() {
	if (is_int()) { return value.int_value; }
	return 0;
}

float JSON::JsonValue::get_float() {
	if (is_float()) { return value.float_value; }
	return 0.0;
}

bool JSON::JsonValue::get_bool() {
	if (is_bool()) { return value.bool_value; }
	return false;
}

JSON::JsonObject* JSON::JsonValue::get_object() {
	if (is_object()) { return value.object; }
	return NULL;
}
JSON::JsonArray* JSON::JsonValue::get_array() {
	if (is_array()) { return value.array; }
	return NULL;
}
