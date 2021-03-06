#pragma once

#include "node.h"

#include <stdio.h>

typedef enum {
	p_default,
	p_start,
	p_block,
	p_property,
	p_attribute,
	p_end
} ParserState;

typedef struct {
	FILE* stream;
	ParserState state;

	char* pos;
	unsigned int current_line;
	unsigned int current_column;

	size_t length;

	char error[128];
} Parser;

//
// Parser interface.
//
int ParseStream(Parser* parser, const char* stream);

