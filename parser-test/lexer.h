#pragma once

#include <stddef.h>

#define BUF_MAX_SIZE	300

typedef struct Token Token;

//
// These structures represent the tokenizer
// more than it does a lexer.
// TODO : Rename this file to tokenizer.h
//

typedef struct {
	Token* token;
	char* data;
} LType;

typedef struct {
	LType* head;

	// TODO : Move these into the LType object.
	LType* next;
	LType* prev;

	// 
	size_t size; //! Linked list length.

	char buffer[BUF_MAX_SIZE];
} LTypeList;

LTypeList* CreateLTypeList();
void ClearLTypeList(LTypeList *list);

void LTypeAddList(LTypeList *list, LType *type);

// Add with the value.
// Resolve the buffer.

LType* LTypeNew(LTypeList* list);

/**
 *
 */
LType* LTypeSetLine(LTypeList* list, const char* str);

LType* LGetNextToken(LType* type);