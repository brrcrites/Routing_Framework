/* File: json_parser.lex
 * Author: Jeffrey McDaniel
 * Date: December 9, 2013
 * Description: Flex file for a JSON parser
 */

%{
#include "json_parser_bison.hh"
#include <string.h>
%}

%option yylineno noyywrap nodefault case-insensitive
	int jsoncolumn = 0;

	/* General tokens */
DIGIT 		[0-9]
DIGIT1 		[1-9]
INTNUM		-?{DIGIT}+
FRACT		"."{DIGIT}+
FLOAT		({INTNUM}|0){FRACT}
EXP			[eE][+-]?{DIGIT}+
NUMBER		-?{FLOAT}{EXP}?

UNICODE 	\\u[A-Fa-f0-9]{4}
ESCAPE 		\\["\\/bfnrt]
CHAR		[^"\\]|{ESCAPE}|{UNICODE}
STRING		\"{CHAR}*\"

%%

.			jsoncolumn++;REJECT;

 	/* General JSON tokens */
"{"								{return '{';}
"}"								{return '}';}
"["								{return '[';}
"]"								{return ']';}
,								{return ',';}
:								{return ':';}
true							{jsonlval.bool_val=true;return TRUE;}
false							{jsonlval.bool_val=false;return FALSE;}
null							{return JSONNULL;}

{STRING}						 {jsonlval.str_val = jsontext;return IDENT;}
{INTNUM}						 {jsonlval.int_val = atoi(jsontext);return INTNUM;}
{NUMBER}						 {jsonlval.float_val = atof(jsontext);return NUMBER;}

[ \t]	/* Do Nothing*/
[\n]	{jsoncolumn = 0;}
.	/* anything else (should have error) */

%%

void clean_flex() {
	yy_delete_buffer(YY_CURRENT_BUFFER);
	yy_init = 1;
	yylex_destroy();
}
