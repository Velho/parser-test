#include "parser.h"
#include "node.h"
#include "token.h"

#include "lexer.h"

#include <stdlib.h>
#include <string.h>


Parser* CreateParser()
{
	return (Parser*)malloc(sizeof(Parser));
}

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


int ParseFile(const char* filename)
{
	Parser* parser;
	FILE* file;
	int err;

	parser = CreateParser();

	file = fopen(filename, "r");
	if (file == NULL) {
		sprintf(parser->error, "ParseFile() => Failed to open the file.");
		return 1;
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

	LxeTokenContext* lexeme_list = CreateTokenContext();;

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
		LxeTokenData* lexeme = LxeSetLine(lexeme_list, buf);
		LxeTokenValue* token;

		while ((token = LxeGetNextToken(lexeme_list, lexeme)) != NULL)
			;

	}

	// Syntax analysis

	return 0;
}
