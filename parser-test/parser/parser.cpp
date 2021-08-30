#include "parser.h"
#include "token.h"
#include "lexer.h"
#include "sem-anal.h"

#include <stdlib.h>
#include <string.h>

// fgets style context.
struct ParserStreamState
{
	const char *stream;
	size_t bytes;
};

/**
 * When parsing a Stream for example
 *
 * @example
 * while (ParserReader(line, max_length, stream) != NULL)
 * {
 * }
 */

// typedef char* (*ParserReaderFn)(char* str, int num, void* stream);
using ParserReader = char *(*)(char *str, int num, void *stream);
// C++11 style of using or C style function pointer?
/* fgets function pointer. */

/**
 * @brief
 *
 * @param stream
 * @return ParserResult
 */
static ParserResult Parse(ParserReader parser, void *stream);

// FIXME : Replace this with a real error-code.
char g_parser_error[128];

static Parser *CreateParser()
{
	return (Parser *)malloc(sizeof(Parser));
}

Parser *InitParser(const char *filename)
{
	Parser *parser = (Parser *)malloc(sizeof(Parser));

	if (parser == NULL)
	{
		sprintf_s(g_parser_error, 128, "InitParser() => Failed to allocate the parser.\n");
		return NULL;
	}

	errno_t err;
	err = fopen_s(&parser->stream, filename, "r");

	if (err)
	{
		sprintf_s(g_parser_error, 128, "InitParser() => Failed to open stream.\n");
		return NULL;
	}

	return parser;
}

ParserResult ParseFile(const char *filename)
{
	FILE *file;
	int f_err;
	ParserResult ret;

	f_err = fopen_s(&file, filename, "r");
	if (f_err)
	{
		sprintf_s(g_parser_error, 128, "Failed to open the given buffer %s.", filename);
		return P_PARSER_FILE_NOT_FOUND;
	}

	ret = Parse((ParserReader)fgets, file);

	// TODO : Handle the Parse return message.
	fclose(file);

	return ret;
}

/*
char g_show_block_filter[] =
{
	"## Comment ##"
	"Show\n\t"
	"Rarity Rare\n"
	"\tHasInfluenceShaper Elder Crusader Redeemer Hunter Warlord\n"
	"\tSetFontSize 45\n"
	"\tMinimapIcon 1 Yellow Circle\n"
	"\tPlayEffect Yellow\n"
	"\tPlayAlertSound 2 300\n"
	"\tDisableDropSound True\n"
};
*/


/*
char* __cdecl fgets(
	_Out_writes_z_(_MaxCount) char* _Buffer,
	_In_                      int   _MaxCount,
	_Inout_                   FILE* _Stream
	);
*/
/**
 * @brief
 * @todo Refer to fgets implementation.
 * @param buffer
 * @param max_count
 * @param stream
 * @return char* Returns one line at the time from the given buffer.
 */
static char* ParseReadString(char *buffer, int max_count, void *stream)
{
	// Read from the buffer until \n and return the result.
	ParserStreamState* stream_state = (ParserStreamState*)stream;
	const char* stream_ptr = stream_state->stream;
	size_t bytes_left = stream_state->bytes;

	// Resulted line.
	char* result = buffer;
	char c;

	// Memory handling is the next concern.
	// Count the amount of characters in oneline if it exceeds some
	// limit e.g. 200, use a dynamically controlled string after that.

	// TODO : Properly implement the max_count.

	if (bytes_left == 0)
	{
		return NULL;
	}

	while (--max_count > 0 && bytes_left != 0)
	{
		// Get the next character from the stream
		// and decrease the read bytes from the stream.
		c = *stream_ptr++;
		bytes_left--;

		// Assign the character into the buffer.
		// Break if we hit a newline.
		*result++ = c;
		if (c == '\n')
		{
			break;
		}
	}

	// Null terminate the resulted line.
	*result = '\0';
	// Update the stream state.
	stream_state->bytes = bytes_left;
	stream_state->stream = stream_ptr;

	return result;
}

ParserResult ParseStream(const char *stream)
{
	ParserResult ret;

	// Passes the call to the Parse(..) function.
	ParserStreamState stream_ctx;
	stream_ctx.stream = stream;
	stream_ctx.bytes = strlen(stream);

	ret = Parse((ParserReader)(ParseReadString), &stream_ctx);

	return P_PARSER_OK;
}

static ParserResult Parse(ParserReader reader, void *stream)
{
	Parser *parser = CreateParser();

	//
	// Parser should map the item filter as a better
	// intermediate even on file level, because the line
	// lengths can be something insane.
	//

	LxeTokenContext *lexeme_list = CreateTokenContext(parser);

	// Buffer size for the given line.
	char buf[BUF_MAX_SIZE];
	while (reader(buf, BUF_MAX_SIZE, stream) != NULL)
	{
		/*
		Lexers and parsers are most often used for compilers,
		but can be used for other computer language tools,
		such as prettyprinters or linters.
		Lexing can be divided into two stages:
		the scanning, which segments the input string
		into syntactic units called lexemes and categorizes
		these into token classes; and the evaluating,
		which converts lexemes into processed values.
		*/

		// TODO : Fix the commented.

		// Build the node list.

		// Token* tok_obj;
		LxeTokenData *lexeme = LxeSetLine(lexeme_list, buf);

		/*tok_obj = TokGetToken(lexeme->buffer);
		SemAssignToken(tok_obj, lexeme);*/

		//
		// Assigning Token Type is different for the TokenData
		// from the TokenValue.
		//

		LxeTokenValue *token;
		while ((token = LxeGetNextToken(lexeme)) != NULL)
		{
			//tok_obj = TokGetToken(token->data, token_length);
			//SemAssignToken(tok_obj, token);
		}
	}

	//
	// Semantics are assigned to the Data and value objects
	// which can be used to retrieve the Sem Token values.
	//

	// Syntax analysis

	//
	// Releasing the managed memory here for the inner structures used by the application.
	//
	// Free up the application data structures.
	SemRelease();
	LxeRelease(parser->ctx_lexer);

	free(parser);

	return 0;
}
