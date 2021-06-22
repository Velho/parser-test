#include "lexer.h"
#include "pdef.h"

#include <string.h>

#define TOKEN_DELIM		" "

LTypeList* CreateLTypeList()
{
	LTypeList* typelist = (LTypeList*)malloc(sizeof(LTypeList));
	return typelist;
}

void ClearLTypeList(LTypeList *list)
{
	LType* last;
	LType* type;

	last = list->next;

	while (last != NULL)
	{
		type = last;
		last = list->next;

		if (type != NULL)
		{
			free(type);
		}
	}
}


void LTypeAddList(LTypeList* list, LType* type)
{
	LType* prev;
	prev = list->next;

	list->prev = prev;
	list->next = type;

	list->size += 1;
}


LType* LTypeNew(LTypeList* list)
{
	return (LType*)malloc(sizeof(LType));
}

LType* LTypeSetLine(LTypeList* list, const char* str)
{
	LType* lexeme;
	char* token;

	strcpy(list->buffer, str);
	lexeme = LTypeNew(list);

	if (lexeme == NULL) {
		// TODO : Output error.
		return NULL;
	}

	// Get the first token.
	token = strtok(list->buffer, TOKEN_DELIM);
	strcpy(lexeme->data, token);

	//
	// TODO : Resolve the enum Token for the given data.
	//

	// TODO : Make sure the AddList is functioning correctly.
	LTypeAddList(list, lexeme);

#ifdef LOG_DBG
	printf("LTypeSetLine() => Token: \t%s\n", token);
#endif
	return lexeme;
}

/*
The call, suggested by the getNextTokencommand, 
causes the lexical analyzer to read characters
from its input until it can identify the next lexeme
and produce for it the next token, which it returns to the parser
*/

LType* LGetNextToken(LType* type)
{
	char* token;

	// 
	// strtok() the passed string.
	//

	token = strtok(NULL, TOKEN_DELIM);

	return NULL;
}