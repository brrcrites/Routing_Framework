
#ifndef _JSON_PARSER_JSON_FILE_H_
#define _JSON_PARSER_JSON_FILE_H_

#include "json_array.h"
#include "json_object.h"
#include "json_name_value.h"

#include <stack>
#include <vector>

#include <cstdlib>

namespace JSON {
	namespace Stack {
		enum StackType {kObject,kArray,kNameValue};
		string type_string(StackType type);
		struct StackItem {
				StackType type;
				union {
					JsonObject* object;
					JsonArray* array;
					JsonNameValue* name_value;
				} value;
				//TODO: How to make this a friend class of JsonFile
				//friend class JsonFile;
				/* Constructors */
				explicit StackItem(StackType new_type);
				void add(JsonObject* new_object);
				void add(JsonArray* new_array);
				void add(JsonNameValue* new_name_value);
		};
	}
	class JsonFile {
		//friend class JSON::Stack::StackItem;
		private:
			std::vector<JsonObject> objects;
			std::vector<JsonNameValue> name_values;
			std::vector<JsonArray> arrays;
			/* Memory Management */
			std::vector<JsonValue*> values;

			// Used for parsing
			std::stack<Stack::StackItem> items;

			/* Helper functions */
			void remove_quotes(char*& quoted);
			void set_current_value(JSON::JsonValue* new_value);
		public:
			/* Constructors */
			JsonFile() { }
			~JsonFile();

			/* Modifiers */
			void create_object();
			void create_array();
			void create_name_value(char* name);
			void set_current_value(char* value);
			void set_current_value(float value);
			void set_current_value(int value);
			void set_current_value(bool value);
			void set_current_value();
			void pop_stack();

			/* Accessors */
			unsigned objects_size() { return objects.size(); }
			JsonObject* objects_at(unsigned index) {
				if (index >= objects.size()) { return NULL; }
				return &objects.at(index);
			}
			unsigned name_values_size() { return name_values.size(); }
			JsonNameValue* name_values_at(unsigned index) {
				if (index >= name_values.size()) { return NULL; }
				return &name_values.at(index);
			}
			JsonValue* name_values_at(const string& key) {
				for (unsigned i = 0;i < name_values.size();i++) {
					if (name_values.at(i).name_matches(key)) { 
						return name_values.at(i).get_value();
					}
				}
				return NULL;
			}

			/* Print functions */
			void print();
			void print_values();
			void print_stack();
	};
}

#endif // _JSON_PARSER_JSON_FILE_H_
