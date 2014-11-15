

#include "json_object.h"

#include <cstdio>

JSON::JsonValue* JSON::JsonObject::find(string key) {
	for (unsigned i = 0;i < name_values.size();i++) {
		if (name_values.at(i)->name_matches(key)) {
			return name_values.at(i)->get_value();
		}
	}
	return NULL;
}
