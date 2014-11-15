/* Filename: json_parser.cc
 * Author: jeffrey
 * Date: Mon Dec  9 11:28:54 PST 2013
 * Description: main function for json_parser
 * 
 * Version: 1.0
*/

#include <iostream>
#include "json_parser.h"
#include "json_parser_bison.hh"

int jsonparse();
extern FILE* jsonin;
int jsonrestart(FILE*);
void clean_flex();
string fn;

JSON::JsonFile* json_file;

void json_parse(string filename,JSON::JsonFile* json_out){
	fn = filename;
	json_file = json_out;
	jsonin = fopen(filename.c_str(),"r");
	if(!jsonin){
		fprintf(stderr,"Error: json: Unable to open \"%s\".\n",filename.c_str());
		return;
	}
	jsonrestart(jsonin);
	jsonparse();
	fclose(jsonin);
	clean_flex();
}
