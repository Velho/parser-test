#include "parser.h"

#include <stdio.h>

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

#define FILTER_PATH "C:/Users/Velho/source/repos/parser-test/Debug/"

//
// Entry-Point
//
int main()
{
	int ret;

	//
	// Implement a console renderer.
	// Console renderer should be dynamic where you can
	// give any input and perform all application actions.
	//

	// Parse the given stream.
	ret = ParseFile(FILTER_PATH "filters/sample1.filter");
	
	// Able to use the same context?

	// ...
	// Profit
}
