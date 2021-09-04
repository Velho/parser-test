#pragma once

#include <stddef.h>

// TODO : OASD Destoryed this. Make more
// Dynamic buffer size?
#define BUF_MAX_SIZE	512

/**
 * These can be quite the long lines.
 * hasExplMods
 * BaseTypes
 *
 * Scrape these websites :
 * https://www.pathofexile.com/item-data
 */

// typedef struct Token Token;
//typedef struct _TokenData LxeTokenValue;

//
// These structures represent the tokenizer
// more than it does a lexer.
// TODO : Rename this file to tokenizer.h
//

struct Parser;

struct LxeTokenValue {
	char data[BUF_MAX_SIZE]; // Replace it with the buffer.
	size_t len;

	struct LxeTokenValue* next;
};


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
struct LxeTokenData {
	LxeTokenValue* head;
	LxeTokenValue* values;
	size_t value_size;

	char* token_ctx;
	char token[BUF_MAX_SIZE];

	// Whole line buffer.
	char buffer[BUF_MAX_SIZE]; //! TODO : Dynamic buffer instead of static.

	//! Doubly linked list.
	struct LxeTokenData* next;
	struct LxeTokenData* prev;

	size_t size; //! Linked list length.
};

typedef void (*LxeTokenDataCallback)(LxeTokenData*);

struct LxeTokenContext {
	LxeTokenData* head;
	LxeTokenData* trail;

	size_t size;
};

char* GetErrorMessage();

LxeTokenContext* CreateTokenContext(struct Parser* parser);
void LxeRelease(LxeTokenContext* ctx); //! Free the memory used the lexer context.

void LTypeAddList(LxeTokenContext* list, LxeTokenData* type); //<! Deprecated.

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
LxeTokenValue* LxeGetNextToken(LxeTokenData* type);