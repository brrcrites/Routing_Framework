

#include "json_file.h"

#include <cstdio>

string JSON::Stack::type_string(StackType type) {
	switch (type) {
		case kObject:
			return "Object";
		case kArray:
			return "Array";
		case kNameValue:
			return "Name-value";
		default:
			return "None";
	}
}

void JSON::Stack::StackItem::add(JsonObject* new_object) {
	JsonValue* new_value = new JsonValue(new_object);
	switch(type) {
		case kNameValue:
			value.name_value->set_value(new_value);
			break;
		case kArray:
			value.array->push_back(new_value);
			break;
		default:
			//Error.
			return;
	}
}

void JSON::Stack::StackItem::add(JsonArray* new_array) {
	JsonValue* new_value = new JsonValue(new_array);
	switch(type) {
		case kArray:
			value.array->push_back(new_value);
			break;
		case kNameValue:
			value.name_value->set_value(new_value);
			break;
		default:
			//Error.
			return;
	}
}

void JSON::Stack::StackItem::add(JsonNameValue* new_name_value) {
	JsonValue* new_value = new JsonValue(new_name_value);
	switch (type) {
		case kArray:
			value.array->push_back(new_value);
			break;
		case kNameValue:
			value.name_value->set_value(new_value);
			break;
		case kObject:
			value.object->push_back(new_name_value);
			break;
		default:
			return;
	}
}

JSON::Stack::StackItem::StackItem(StackType new_type):type(new_type) {
	switch(new_type) {
		case kObject:
			value.object = new JsonObject();
			break;
		case kArray:
			value.array = new JsonArray();
			break;
		case kNameValue:
			value.name_value = new JsonNameValue();
			break;
	}
}

JSON::JsonFile::~JsonFile() {
	int values_deleted = 0;
	int values_size_deleted = 0;
	for (unsigned i = 0;i < values.size();i++) {
		values_deleted++;
		values_size_deleted+=sizeof(values.at(i));
		delete(values.at(i));
	}
	int stack_deleted = 0;
	int stack_size_deleted = 0;
	while (!items.empty()) {
		Stack::StackItem current = items.top();
		items.pop();
		stack_deleted++;
		stack_size_deleted+=sizeof(&current);
	}
	/*fprintf(stderr,"Deleted (%d):\n\tValues: %d(%d)\n\tStack: %d(%d)\n",
			values_size_deleted+stack_size_deleted,
			values_deleted,values_size_deleted,
			stack_deleted,stack_size_deleted);*/
}

void JSON::JsonFile::create_array() {
	Stack::StackItem new_item(Stack::kArray);
	items.push(new_item);
}

void JSON::JsonFile::create_object() {
	Stack::StackItem new_item(Stack::kObject);
	items.push(new_item);
}

void JSON::JsonFile::create_name_value(char* name) {
	remove_quotes(name);
	JsonNameValue* new_name_value = new JsonNameValue(name);
	//name_values.push_back(new_name_value);
	Stack::StackItem new_item(Stack::kNameValue);
	new_item.value.name_value = new_name_value;
	items.push(new_item);
}

void JSON::JsonFile::remove_quotes(char*& quoted) {
	if (*quoted == '\"') { quoted+=1; }
	char* find_quote = quoted;
	while (*find_quote != '\"' && *find_quote != '\0') { find_quote++; }
	*find_quote = '\0';
}

void JSON::JsonFile::set_current_value(char* value) {
	remove_quotes(value);
	JSON::JsonValue* new_value = new JSON::JsonValue(value);
	values.push_back(new_value);
	set_current_value(new_value);
}

void JSON::JsonFile::set_current_value(float value) {
	JSON::JsonValue* new_value = new JSON::JsonValue(value);
	values.push_back(new_value);
	set_current_value(new_value);
}

void JSON::JsonFile::set_current_value(int value) {
	JSON::JsonValue* new_value = new JSON::JsonValue(value);
	values.push_back(new_value);
	set_current_value(new_value);
}

void JSON::JsonFile::set_current_value() {
	JSON::JsonValue* new_value = new JSON::JsonValue();
	values.push_back(new_value);
	set_current_value(new_value);
}
	
void JSON::JsonFile::set_current_value(bool value) {
	JSON::JsonValue* new_value = new JSON::JsonValue(value);
	values.push_back(new_value);
	set_current_value(new_value);
}

void JSON::JsonFile::set_current_value(JSON::JsonValue* new_value) {
	if (items.empty()) {
		return;
	}
	Stack::StackItem top_item = items.top();
	switch (top_item.type) {
		case Stack::kArray:
			top_item.value.array->push_back(new_value);
			break;
		case Stack::kNameValue:
			top_item.value.name_value->set_value(new_value);
			break;
		default:
			//Error.
			return;
	}
}

void JSON::JsonFile::pop_stack() {
	if (items.empty()) {
		return;
	}
	Stack::StackItem popped = items.top();
	items.pop();
	if (items.empty()) { 
		switch (popped.type) {
			case Stack::kObject:
				objects.push_back(*(popped.value.object));
				break;
			case Stack::kNameValue:
				name_values.push_back(*(popped.value.name_value));
				break;
			default:
				return;
		}
		return; 
	}
	Stack::StackItem top_item = items.top();
	switch (popped.type) {
		case Stack::kObject:
			top_item.add(popped.value.object);
			break;
		case Stack::kArray:
			arrays.push_back(*(popped.value.array));
			top_item.add(popped.value.array);
			break;
		case Stack::kNameValue:
			top_item.add(popped.value.name_value);
			break;
		default:
			return;
	}
}

void JSON::JsonFile::print() {
	fprintf(stderr,"%d objects loaded.\n",objects.size());
	fprintf(stderr,"%d Name Values loaded.\n",name_values.size());
	for (unsigned i = 0;i < name_values.size();i++) {
		fprintf(stderr,"\t%s",name_values.at(i).get_name().c_str());
		fprintf(stderr,": %s",name_values.at(i).get_value()->type_string().c_str());
		if (name_values.at(i).get_value()->is_array()) {
			fprintf(stderr," (%d)\n",name_values.at(i).get_value()->get_array()->size());
			for (unsigned j = 0;j < name_values.at(i).get_value()->get_array()->size();j++) {
				fprintf(stderr,"\t\t%s\n",name_values.at(i).get_value()->get_array()->at(j)->type_string().c_str());
			}
		} else {
			fprintf(stderr,"\n");
		}
	}
	fprintf(stderr,"%d Arrays loaded.\n",arrays.size());
}

void JSON::JsonFile::print_values() {
	fprintf(stderr,"%d values loaded.\n",values.size());
	for (unsigned i = 0;i < values.size();i++) {
		//fprintf(stderr,"%d: \"%s\"\n",i,values.at(i)->type_string().c_str());
	}
}

void JSON::JsonFile::print_stack() {
	std::vector<Stack::StackItem> stack_order;
	while(!items.empty()) {
		Stack::StackItem current = items.top();
		items.pop();
		stack_order.push_back(current);
	}
	fprintf(stderr,"%d values in stack.\n",stack_order.size());
	for (unsigned i = 0;i < stack_order.size();i++) {
		fprintf(stderr,"%d: \"%s\"\n",i,Stack::type_string(stack_order.at(i).type).c_str());
	}
	for (int i = stack_order.size()-1;i >= 0;i--) {
		items.push(stack_order.at(i));
	}
}
