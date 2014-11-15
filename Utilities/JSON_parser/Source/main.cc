/* Filename: main.cc
 * Author: jeffrey
 * Date: Mon Dec  9 11:28:54 PST 2013
 * Description: main function for json_parser
 * 
 * Version: 1.0
*/

#include "json_file.h"
#include "json_parser.h"

#include <cstdio>

#define MIN_ARGS 2

int main(int argc,char* argv[]){
    if(argc < MIN_ARGS){
        fprintf(stderr,"Error: json_parser <filename>.\n");
        return 1;
    }
	JSON::JsonFile json_file;
	json_parse(argv[1],&json_file);

	json_file.print();
	json_file.print_values();
	json_file.print_stack();

	return 0;
}

