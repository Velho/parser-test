#pragma once

#include "token.h"

#include <stddef.h>

#define BUF_MAX_SIZE	512

// typedef struct Token Token;
//typedef struct _TokenData LxeTokenValue;

//
// These structures represent the tokenizer
// more than it does a lexer.
// TODO : Rename this file to tokenizer.h
//

typedef struct _LxeTokenValue {
	char data[BUF_MAX_SIZE]; // Replace it with the buffer.
	size_t len;

	struct _LxeTokenValue* next;
} LxeTokenValue;


//
// TODO : Fix the TokenData and TokenDataList structs.
// TODO : Fix the documentation.
// 
// Implements the Doubly Linked List.
// While linked list is traversable one way
// thro the next pointer, but with the Doubly
// linked list it's possible to traverse in reverse.
// 
// In this use case where we build sequental list from
// start of the file to the end, it's prolly not needed
// the ability to traverse it in both ways.
// Doubly linked list is described with quick operations,
// efficient insertion and removal at any given position.
//
typedef struct _LxeTokenData {
	LxeTokenValue* head;
	LxeTokenValue* values;
	size_t value_size;

	char* token_ctx;
	char token[BUF_MAX_SIZE];

	// Whole line buffer.
	char buffer[BUF_MAX_SIZE]; //! TODO : Dynamic buffer instead of static.

	//! Doubly linked list.
	struct _LxeTokenData* next;
	struct _LxeTokenData* prev;

	size_t size; //! Linked list length.
} LxeTokenData;

typedef void (*LxeTokenDataCallback)(LxeTokenData*);

typedef struct {
	LxeTokenData* head;
	LxeTokenData* trail;

	size_t size;
} LxeTokenContext;

char* GetErrorMessage();

LxeTokenContext* CreateTokenContext();
void ClearLTypeList(LxeTokenContext*list);

void LTypeAddList(LxeTokenContext*list, LxeTokenData* type); //<! Deprecated.

void LxeInsertBegin(LxeTokenContext* list, LxeTokenData* token);
void LxeInsertEnd(LxeTokenContext* list, LxeTokenData* token);

void LxeInsertBefore(LxeTokenContext* list, LxeTokenData* token, LxeTokenData* newtoken);
void LxeInsertAfter(LxeTokenContext* list, LxeTokenData* token, LxeTokenData* newtoken);

void LxeTraverseList(LxeTokenContext* list, LxeTokenDataCallback cb);

// LxeTokenData* LxeNewToken(Token* token, char* data);

LxeTokenValue* LxeInsertNode(LxeTokenData* token, char * data);

/**
 *
 */
LxeTokenData* LxeSetLine(LxeTokenContext* list, const char* str);

/**
 *
 */
LxeTokenValue* LxeGetNextToken(LxeTokenContext* list, LxeTokenData* type);