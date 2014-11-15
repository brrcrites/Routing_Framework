
#ifndef _JSON_PARSER_JSON_OBJECT_H_
#define _JSON_PARSER_JSON_OBJECT_H_

#include "json_name_value.h"

#include <vector>

namespace JSON {
	class JsonValue;
	class JsonObject{
		private:
			std::vector<JsonNameValue*> name_values;
		public:
			/* Constructors */

			/* Modifiers */
			void push_back(JsonNameValue* new_value) { name_values.push_back(new_value); }

			/* Accessors */
			JsonValue* find(string key);
			unsigned size() { return name_values.size(); }
			JsonNameValue* at(unsigned index) {
				if (index >= name_values.size()) {
					return NULL;
				}
				return name_values.at(index);
			}
	};
}

#endif // _JSON_PARSER_JSON_OBJECT_H_
