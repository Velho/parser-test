#include "lexer.h"
#include "pdef.h"

#include "token.h"

#include "parser.h"

#include <stdlib.h>
#include <string.h>

#define TOKEN_DATA_DELIM		" "
#define ERROR_BUFFER_LEN		128

// MSVC is defined, don't care about the resulting value.
#ifdef _MSC_VER
// TODO : Redefine it to something else on different platforms.

/**
 * @brief Returns the String size in bytes.
 */
#define LxeStrSizeInBytes(str)		_countof(str)
#endif

char g_lex_error[ERROR_BUFFER_LEN];


char* GetErrorMessage()
{
	return g_lex_error;
}

LxeTokenContext* CreateTokenContext(Parser* parser)
{
	LxeTokenContext* typelist = (LxeTokenContext*)malloc(sizeof(LxeTokenContext));

	// Assign the lexer context to the parser object.
	parser->ctx_lexer = typelist;

	typelist->head = NULL;
	typelist->trail = NULL;
	typelist->size = 0;

	return typelist;
}

static void LxeReleaseTokenValue(LxeTokenData* data)
{
	LxeTokenValue* head;
	LxeTokenValue* temp;

	head = data->head;
	temp = data->head;

	while (temp != NULL)
	{
		temp = head->next;
		free(head);

		head = temp;
	}
}

static void LxeReleaseTokenData(LxeTokenContext* list)
{
	LxeTokenData* last;
	LxeTokenData* type;

	// TODO : Remove the singly linked list as well
	// under the LxeTokenData -> head of type TokenValue.

	// head->prev == NULL , this stmnt should apply.
	last = list->head->next;

	while (last != NULL)
	{
		type = last;
		last = type->next;

		if (type != NULL)
		{
			// Release the token values before losing the data pointer forever.
			LxeReleaseTokenValue(type);
			free(type);
		}
	}
}

void LxeRelease(LxeTokenContext* ctx)
{
	// Release the TokenDats from head to trail.
	LxeReleaseTokenData(ctx);
	// Free the lexer context.
	free(ctx);
}


void LTypeAddList(LxeTokenContext* list, LxeTokenData* type)
{
	LxeTokenData* prev;
	prev = type->next;

	type->prev = prev;
	type->next = type;

	list->trail = type;
	list->size += 1;
}

/*
function insertBeginning(List list, Node newNode)
	if list.firstNode == null
		list.firstNode  := newNode
		list.lastNode   := newNode
		newNode.prev  := null
		newNode.next  := null
	else
		insertBefore(list, list.firstNode, newNode)
*/
void LxeInsertBegin(LxeTokenContext* list, LxeTokenData* token)
{
	if (list->head == NULL)
	{
		// TODO : Logic behind this..?
		list->head = token;
		list->trail = token;
		token->prev = NULL;
		token->next = NULL;
	}
	else
	{
		LxeInsertBefore(list, list->trail, token);
	}
}

/*
function insertEnd(List list, Node newNode)
	 if list.lastNode == null
		 insertBeginning(list, newNode)
	 else
		 insertAfter(list, list.lastNode, newNode)
*/
void LxeInsertEnd(LxeTokenContext* list, LxeTokenData* token)
{
	if (list->trail == NULL)
	{
		LxeInsertBegin(list, token);
	}
	else
	{
		LxeInsertAfter(list, list->trail, token);
	}
}

/*
function insertBefore(List list, Node node, Node newNode)
	newNode.next  := node
	if node.prev == null
		newNode.prev  := null -- (not always necessary)
		list.firstNode  := newNode
	else
		newNode.prev  := node.prev
		node.prev.next  := newNode
	node.prev  := newNode
*/
void LxeInsertBefore(LxeTokenContext* list, LxeTokenData* token, LxeTokenData* newtoken)
{
	newtoken->next = token;

	if (token->prev == NULL)
	{
		newtoken->prev = NULL; // Not always necesary.
		list->head = newtoken;
	}
	else
	{
		newtoken->prev = token->prev;
		token->prev->next = newtoken;
	}

	token->prev = newtoken;
}

/*
function insertAfter(List list, Node node, Node newNode)
	newNode.prev  := node
	if node.next == null
		newNode.next  := null -- (not always necessary)
		list.lastNode  := newNode
	else
		newNode.next  := node.next
		node.next.prev  := newNode
	node.next  := newNode
*/
void LxeInsertAfter(LxeTokenContext* list, LxeTokenData* token, LxeTokenData* newtoken)
{
	newtoken->prev = token;

	if (token->next == NULL)
	{
		newtoken->next = NULL; // Not always necessary.
		list->trail = newtoken;
	}
	else
	{
		newtoken->next = token->next;
		token->next->prev = newtoken;
	}
	token->next = newtoken;
}

void LxeTraverseList(LxeTokenContext* list, LxeTokenDataCallback cb)
{
	LxeTokenData* temp = list->head;

	while (temp != NULL)
	{
		cb(temp);
		temp = temp->next;
	}
}

static LxeTokenValue* LxeNewTokenValue(const char* str, size_t len)
{
	LxeTokenValue* token_value = (LxeTokenValue*)malloc(sizeof(LxeTokenValue));

	token_value->next = NULL;

	// Do we need add the \0.
	strcpy_s(token_value->data, LxeStrSizeInBytes(token_value->data), str);
	token_value->len = len;

	return token_value;
}

LxeTokenValue* LxeInsertNode(LxeTokenData* /* head */ token, char* data)
{
	// Create new value with the given data.
	// Adds the newly created value to the linked list.

	size_t datalen;
	struct LxeTokenValue* temp;
	struct LxeTokenValue* p;

	datalen = strnlen_s(data, BUF_MAX_SIZE);

	// temp = (LxeTokenValue*)malloc(sizeof(LxeTokenValue));
	temp = LxeNewTokenValue(data, datalen);
	if (temp == NULL)
	{
		// Failed allocation.
		sprintf_s(g_lex_error, ERROR_BUFFER_LEN, "LxeInsertNode(..) => Failed allocation of new TokenValue.\n");
		return NULL;
	}

	// Done in the allocation.
	// strcpy_s(temp->data, LxeStrSizeInBytes(temp->data), data);

	if (token->head == NULL)
	{
		token->head = temp;
	}
	else
	{
		p = token->head;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = temp;
		token->size++;
	}

	return temp;
}

static LxeTokenData* LxeNewTokenData(const char* str)
{
	LxeTokenData* token_dat;
	size_t str_len;

	token_dat = (LxeTokenData*)malloc(sizeof(LxeTokenData));
	str_len = strnlen_s(str, BUF_MAX_SIZE);

	if (token_dat == NULL)
	{
		return NULL;
	}
	//     _ACRTIMP errno_t __cdecl strcpy_s(
	//_Out_writes_z_(_SizeInBytes) char* _Destination,
	//	_In_                         rsize_t     _SizeInBytes,
	//	_In_z_                       char const* _Source
	strcpy_s(token_dat->buffer, LxeStrSizeInBytes(token_dat->buffer), str);

	token_dat->head = NULL;
	token_dat->values = NULL;
	token_dat->size = 0;

	return token_dat;
}

LxeTokenData* LxeSetLine(LxeTokenContext* list, const char* str)
{

	//
	// Allocates and set's the first TokenData.
	//

	LxeTokenData* lexeme;
	char* token;
	size_t len;

	// TODO : Do we need the size anymore? Anyother use when the alloc
	// is made in the func NewTokenDat.
	len = strnlen_s(str, BUF_MAX_SIZE);
	lexeme = LxeNewTokenData(str);

	if (lexeme == NULL)
	{
		sprintf_s(g_lex_error, ERROR_BUFFER_LEN, "LxeSetLine() => Failed to allocate new LxeTokenData.\n");
		return NULL;
	}

	// Get the first token.
	token = strtok_s((char*)str, TOKEN_DATA_DELIM, &lexeme->token_ctx);
	printf("Tokenizer context : %p\n", lexeme->token_ctx);

	if (token == NULL)
	{
		sprintf_s(g_lex_error, ERROR_BUFFER_LEN, "LxeSetLine() => Failed to tokenize the string.\n");
		return lexeme;
	}

	len = strnlen_s(token, BUF_MAX_SIZE);

	// Set the data to Lxe object.
	strcpy_s(lexeme->token, LxeStrSizeInBytes(lexeme->token), token); // len + 1 (??)

	// Add the Lxe object to end of the list.
	LxeInsertEnd(list, lexeme);

#ifdef DEBUG_LOGGER
	printf("LxeSetLine() => Token: \t%s\n", token);
#endif
	return lexeme;
}

LxeTokenValue* LxeGetNextToken(LxeTokenData* type)
{
	char* token;
	//size_t token_len;
	LxeTokenValue* lxe_token;

	//
	// strtok_s() the passed string.
	// Tokenization is started in the SetLine function,
	// so it can be called with NULL and token_ctx.
	//
	// Make a new allocation for the passed in type.
	//

	token = strtok_s(NULL, TOKEN_DATA_DELIM, &type->token_ctx);
	if (token == NULL)
	{
		// Tokenizer is finished.
		return NULL;
	}

	lxe_token = LxeInsertNode(type, token);

#ifdef DEBUG_LOGGER
	printf("LxeGetNextToken() => Next Token: \t%s\tLen => %zu\n", lxe_token->data, type->size);
#endif

	return lxe_token;
}
