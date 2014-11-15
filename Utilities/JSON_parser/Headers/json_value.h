
#ifndef _JSON_PARSER_JSON_VALUE_H_
#define _JSON_PARSER_JSON_VALUE_H_

#include <string>

using std::string;

namespace JSON {
	class JsonObject;
	class JsonArray;

	enum kJsonType {kString,kInt,kFloat,kBool,kObject,kArray,kNull,kNone};
	string type_string(kJsonType type);

	class JsonValue {
		private:
			kJsonType type;
			union {
				string* string_value;
				int int_value;
				float float_value;
				bool bool_value;
				JsonObject* object;
				JsonArray* array;
				void* null;
			} value;
		public:
			/* Constructors */
			JsonValue(char* new_value): type(kString) { value.string_value = new string(new_value); }
			JsonValue(float new_value): type(kFloat) { value.float_value = new_value; }
			JsonValue(int new_value): type(kInt) { value.int_value = new_value; }
			JsonValue(bool new_value): type(kBool) { value.bool_value = new_value; }
			JsonValue(JsonObject* new_value): type(kObject) { value.object = new_value; }
			JsonValue(JsonArray* new_value): type(kArray) { value.array = new_value; }
			JsonValue():type(kNull) { value.null = NULL; }
			~JsonValue();
			JsonValue* operator=(const JsonValue& rhs) {
				type = rhs.type;
				value = rhs.value;
				return this;
			}

			/* Accessors */
			string type_string() { return JSON::type_string(type); }
			bool is_string() { return type == kString; }
			bool is_int() { return type == kInt; }
			bool is_float() { return type == kFloat; }
			bool is_bool() { return type == kBool; }
			bool is_object() { return type == kObject; }
			bool is_array() { return type == kArray; }
			bool is_null() { return type == kNull; }

			int size_of();
			string get_string();
			int get_int();
			float get_float();
			bool get_bool();
			JsonObject* get_object();
			JsonArray* get_array();
	};
}

#endif // _JSON_PARSER_JSON_VALUE_H_
