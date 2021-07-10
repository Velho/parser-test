#include "token.h"

#include <string.h>


const ConditionToken condition_tokens[] =
{
	/*{.token = e_show, .data = "Show"},
	{.token = e_hide, .data = "Hide" },*/
	{.token = E_ALTQUAL, .data = "AlternateQuality" },
	{.token = E_ANYENCH, .data = "AnyEnchantment" },
	{.token = E_AREALVL, .data = "AreaLevel"},
	{.token = E_BASETYPE, .data = "BaseType" },
	{.token = E_BLIGHTMAP, .data = "BlightedMap" },
	{.token = E_CLASS, .data = "Class" },
	{.token = E_CORRUPTED, .data = "Corrupted"},
	{.token = E_CORRUPTEDMOD, .data = "CorruptedMods"},
	{.token = E_DROPLVL, .data = "DropLevel"},
	{.token = E_ELDERITEM, .data = "ElderItem"},
	{.token = E_ELDERMAP, .data = "ElderMap"},
	{.token = E_ENCHPASSNODE, .data = "EnchantmentPassiveNode"},
	{.token = E_ENCHPASSNUM, .data = "EnchantmentPassiveNum" },
	{.token = E_FRACTITEM, .data = "FracturedItem" },
	{.token = E_GEMLEVEL, .data = "GemLevel" },
	{.token = E_GEMQUALTYPE, .data = "GemQualityType" },
	{.token = E_HASENCH, .data = "HasEnchantment" },
	{.token = E_HASEXPLMOD, .data = "HasExplicitMod" },
	{.token = E_HASINFL, .data = "HasInfluence" },
	{.token = E_HEIGHT, .data = "Height" },
	{.token = E_IDENTIFIED, .data = "Identified" },
	{.token = E_ITEMLVL, .data = "ItemLevel" },
	{.token = E_LINKEDSOCKETS, .data = "LinkedSockets" },
	{.token = E_MAPTIER, .data = "MapTier" },
	{.token = E_MIRRORED, .data = "Mirrored" },
	{.token = E_PROPHECY, .data = "Prophecy" },
	{.token = E_QUALITY, .data = "Quality" },
	{.token = E_RARITY, .data = "Rarity" },
	{.token = E_REPLICA, .data = "Replica" },
	{.token = E_SHAPEDMAP, .data = "ShapedMap" },
	{.token = E_SHAPERITEM, .data = "ShaperItem" },
	{.token = E_SOCKETGROUP, .data = "SocketGroup" },
	{.token = E_SOCKETS, .data = "Sockets" },
	{.token = E_STACKSIZE, .data = "StackSize" },
	{.token = E_SYNTHITEM, .data = "SynthesisedItem" },
	{.token = E_WIDTH, .data = "Width" },
};

const ActionToken action_tokens[] =
{
	{.token = E_CUSTOM_ALERT_SND, .data = "CustomAlertSound"},
	{.token = E_DISABLE_DROP_SND, .data = "DisableDropSound"},
	{.token = E_ENABLE_DROP_SND, .data = "EnableDropSound"},
	{.token = E_MINIMAPICON, .data = "MinimapIcon"},
	{.token = E_PLAY_ALERT_SND, .data = "PlayAlertSound"},
	{.token = E_PLAY_ALERT_POS, .data = "PlayAlertSoundPositional"},
	{.token = E_PLAY_EFFECT, .data = "PlayEffect"},
	{.token = E_SET_BG_COLOR, .data = "SetBackgroundColor"},
	{.token = E_SET_BORDER_COLOR, .data = "SetBorderColor"},
	{.token = E_SET_FONT_SIZE, .data = "SetFontSize"},
	{.token = E_SET_TEXT_COLOR, .data = "SetTextColor"},
};

/**
 * TODO : There's deprecated set of Operators
 * with the exact same token but data is different.
 * E.g. token E_EQUAL with data "Equals".
 * Should it be supported? If so add it.
 */
const OperatorToken operator_tokens[] =
{
	{.token = E_EQUAL, .data = "="},
	{.token = E_NOT_EQUAL, .data = "!"},
	{.token = E_LESS_THAN_EQUAL, .data = "<="},
	{.token = E_GREATER_THAN_EQUAL, .data = ">="},
	{.token = E_LESS_THAN, .data = "<"},
	{.token = E_GREATER_THAN, .data = ">"},
	{.token = E_EXACT, .data = "=="},
};

const BlockToken block_tokens[] =
{
	{.token = E_COMMENT, .data = "#"},
	{.token = E_SHOW, .data = "Show"},
	{.token = E_HIDE, .data = "Hide"},
	{.token = E_CONTINUE, .data = "Continue"},
};

ConditionToken* cond_token_get_by_str(char* data)
{
	ConditionToken* tk;

	for (tk = condition_tokens; tk != NULL; tk++)
	{
		if (strcmp(tk->data, data) == 0)
		{
			return tk;
		}
	}

	return NULL;
}

ActionToken* act_token_get_by_str(char* data)
{
	ActionToken* tk;

	for (tk = action_tokens; tk != NULL; tk++)
	{
		if (strcmp(tk->data, data) == 0)
		{
			return tk;
		}
	}

	return NULL;
}

OperatorToken* op_token_get_by_str(char* data)
{
	OperatorToken* tk;

	for (tk = operator_tokens; tk != NULL; tk++)
	{
		if (strcmp(tk->data, data) == 0)
		{
			return tk;
		}
	}

	return NULL;
}

BlockToken* blk_token_get_by_str(char* data)
{
	BlockToken* tk;

	for (tk = block_tokens; tk != NULL; tk++)
	{
		if (strcmp(tk->data, data) == 0)
		{
			return tk;
		}
	}

	return NULL;
}
