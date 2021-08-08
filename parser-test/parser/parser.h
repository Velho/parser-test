#pragma once

#include <stdio.h>

typedef enum {
	p_default,
	p_start,
	p_block,
	p_property,
	p_attribute,
	p_end
} ParserState;

struct _LxeTokenContext;

typedef struct _Parser {
	FILE* stream;
	ParserState state;

	char* pos;
	unsigned int current_line;
	unsigned int current_column;

	size_t length;

	char error[128];
	struct _LxeTokenContext* lexer_ctx;
} Parser;

Parser* CreateParser();

//
// Pass the Parser as argument?
//

int ParseStream(void* stream);
int ParseFile(const char* filename);

