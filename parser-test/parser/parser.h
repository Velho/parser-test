#pragma once

#include <stdio.h>

//
// Current parser is implement for read only operations
// at the moment, perhaps when the time comes to make
// direct edits to the given file, create different module
// called "editor" for example to handle the write operations.
//

enum ParserError {
	P_PARSER_OK,
	P_PARSER_ERROR,
	P_PARSER_FILE_NOT_FOUND
};

typedef int ParserResult;
struct LxeTokenContext;

struct Parser {
	FILE* stream;

	char* pos;
	unsigned int current_line;
	unsigned int current_column;

	size_t length;

	char error[128];
	struct LxeTokenContext* ctx_lexer;
};

Parser* CreateParser();

//
// Pass the Parser as argument?
//

int ParseStream(void* stream);
int ParseFile(const char* filename);

