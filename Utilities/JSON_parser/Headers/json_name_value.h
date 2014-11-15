
#ifndef _JSON_PARSER_JSON_NAME_VALUE_H_
#define _JSON_PARSER_JSON_NAME_VALUE_H_

#include "json_value.h"

namespace JSON {
	class JsonNameValue {
		private:
			string name;
			JsonValue* value;
		public:
			/* Constructors */
			JsonNameValue():value(NULL) { }
			explicit JsonNameValue(string new_name);

			/* Modifiers */
			void set_value(JsonValue* new_value) { value = new_value; }

			/* Accessors */
			string get_name() { return name; }
			bool name_matches(const string& key) { return !name.compare(key); }
			JsonValue* get_value() { return value; }
	};
}

#endif // _JSON_PARSER_JSON_NAME_VALUE_H_
