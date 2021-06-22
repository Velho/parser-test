#include "parser.h"
#include "node.h"
#include "token.h"

#include "lexer.h"

#include <stdlib.h>
#include <string.h>

Parser* InitParser(const char* filename) {
	Parser* parser = (Parser*)malloc(sizeof(Parser));

	if (parser == NULL) {
		// sprintf(parser->error, "InitParser() => Failed to allocate the parser.\n");
		return NULL;
	}

	parser->stream = fopen(filename, "r");

	if (parser->stream == NULL) {
		sprintf(parser->error, "InitParser() => Failed to open stream.\n");
		return NULL;
	}

	return parser;
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
int ParseStream(Parser* parser, void* stream)
{
	// 
	// While loop as tokenizer?
	//

	LTypeList* lexeme_list = CreateLTypeList();

	// Buffer size for the given line.
	char buf[BUF_MAX_SIZE];
	while (fgets(buf, BUF_MAX_SIZE, stream) != NULL) {
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
		LType* token;
		LType* lexeme = LTypeSetLine(lexeme_list, buf);

		// Loop thro the tokens?
		while ((token = LGetNextToken(lexeme)) != NULL) {
			LTypeAddList(lexeme_list, token);
		}
	}

	// Syntax analysis

	return 0;
}

int ParseFile(Parser* parser, const char* filename)
{
	// Should we open the file here.
	FILE* file;
	int err;

	file = fopen(filename, "r");
	if (file == NULL) {
		sprintf(parser->error, "ParseFile() => Failed to open the file.");
		return 1;
	}

	err = ParseStream(parser, file);

	fclose(file);
	return 0;
}
