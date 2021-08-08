#include "parser.h"
#include "token.h"
#include "lexer.h"
#include "sem-anal.h"

#include <stdlib.h>
#include <string.h>

char g_parser_error[128];

Parser* CreateParser()
{
	return (Parser*)malloc(sizeof(Parser));
}

Parser* InitParser(const char* filename) {
	Parser* parser = (Parser*)malloc(sizeof(Parser));

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


int ParseFile(const char* filename)
{
	FILE* file;
	int err;

	err = fopen_s(&file, filename, "r");

	if (err)
	{
		sprintf_s(g_parser_error, 128, "Failed to open the given buffer %s.", filename);
		return err;
	}

	err = ParseStream(file);
	fclose(file);

	return err;
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
int ParseStream(void* stream)
{
	Parser* parser = CreateParser();
	
	// 
	// While loop as tokenizer?
	//

	LxeTokenContext* lexeme_list = CreateTokenContext(parser);

	// Buffer size for the given line.
	char buf[BUF_MAX_SIZE];
	while (fgets(buf, BUF_MAX_SIZE, (FILE*)stream) != NULL) {
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

		// Build the node list.
		Token* tok_obj;
		LxeTokenData* lexeme = LxeSetLine(lexeme_list, buf);

		tok_obj = TokGetToken(lexeme->buffer);
		SemAssignToken(tok_obj, lexeme);

		//
		// Assigning Token Type is different for the TokenData
		// from the TokenValue.
		//

		LxeTokenValue* token;
		while ((token = LxeGetNextToken(lexeme)) != NULL)
		{
			tok_obj = TokGetToken(token->data);
			SemAssignToken(tok_obj, token);
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
	LxeRelease(parser->lexer_ctx);

	return 0;
}
