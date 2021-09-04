#include "parser.h"

// #include "window/window.h"

#include <stdio.h>

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

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

char g_hide_block_filter[] =
{
	"## Comment"
	"Hide\n\t"
	"\tRarity Rare\n"
	"\tClass \"One Hand Maces\"\n"
	"DisableDropSound True\n"
	"# Second hide #"
	"Hide\n"
	"\tRarity Rare\n"
	"\tClass \"Staves\" \"Warstaves\" \"Two Hand Swords\" \"Two Hand Maces\"\n"
	"\tLinkedSockets < 5\n"
	"\tSockets < 6\n"
	"DisableDropSound True"
};

#define FILTER_PATH		"C:/Users/Velho/source/repos/parser/filters/"
#define F_SAMPLE_1		"sample1.filter"
#define F_SAMPLE_2		"sample2.filter"

#define FILTER_EXPAND_N(P, F) 	P ## F
#define STRING_EXPAND(S, E)		FILTER_EXPAND_N(S, E)

//
// Entry-Point
// TODO : Add support for the parsing the array from line 21 e.g.
// TODO : Fix the obvious application wide issues...... kekw
// TODO : Implement the error handlers.
// TODO : Consider using the WinMain for main function.
//
// int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	int retVal;

	//
	// Implement a console renderer.
	// Console renderer should be dynamic where you can
	// give any input and perform all application actions.
	//

	if (!ParseStream(g_hide_block_filter))
	{
		printf("Failed to parse the stream.\n");
		retVal = -1;
	}

	// Parse the given stream.
	// retVal = ParseFile(FILTER_EXPAND(FILTER_PATH, F_SAMPLE_1)); // "filters/sample2.filter"

	// ret = Parse();

	// Able to use the same context?

	// ...
	// Profit
	return retVal;
}
