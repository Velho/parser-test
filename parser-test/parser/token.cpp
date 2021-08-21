#include "token.h"

#include <stdlib.h>
#include <string.h>


const ConditionToken condition_tokens[] =
{
	/*{e_show, "Show"},
	{e_hide, "Hide" },*/
	{E_ALTQUAL, "AlternateQuality" },
	{E_ANYENCH, "AnyEnchantment" },
	{E_AREALVL, "AreaLevel"},
	{E_BASETYPE, "BaseType" },
	{E_BLIGHTMAP, "BlightedMap" },
	{E_CLASS, "Class" },
	{E_CORRUPTED, "Corrupted"},
	{E_CORRUPTEDMOD, "CorruptedMods"},
	{E_DROPLVL, "DropLevel"},
	{E_ELDERITEM, "ElderItem"},
	{E_ELDERMAP, "ElderMap"},
	{E_ENCHPASSNODE, "EnchantmentPassiveNode"},
	{E_ENCHPASSNUM, "EnchantmentPassiveNum" },
	{E_FRACTITEM, "FracturedItem" },
	{E_GEMLEVEL, "GemLevel" },
	{E_GEMQUALTYPE, "GemQualityType" },
	{E_HASENCH, "HasEnchantment" },
	{E_HASEXPLMOD, "HasExplicitMod" },
	{E_HASINFL, "HasInfluence" },
	{E_HEIGHT, "Height" },
	{E_IDENTIFIED, "Identified" },
	{E_ITEMLVL, "ItemLevel" },
	{E_LINKEDSOCKETS, "LinkedSockets" },
	{E_MAPTIER, "MapTier" },
	{E_MIRRORED, "Mirrored" },
	{E_PROPHECY, "Prophecy" },
	{E_QUALITY, "Quality" },
	{E_RARITY, "Rarity" },
	{E_REPLICA, "Replica" },
	{E_SHAPEDMAP, "ShapedMap" },
	{E_SHAPERITEM, "ShaperItem" },
	{E_SOCKETGROUP, "SocketGroup" },
	{E_SOCKETS, "Sockets" },
	{E_STACKSIZE, "StackSize" },
	{E_SYNTHITEM, "SynthesisedItem" },
	{E_WIDTH, "Width" },
};

const ActionToken action_tokens[] =
{
	{E_CUSTOM_ALERT_SND, "CustomAlertSound"},
	{E_DISABLE_DROP_SND, "DisableDropSound"},
	{E_ENABLE_DROP_SND, "EnableDropSound"},
	{E_MINIMAPICON, "MinimapIcon"},
	{E_PLAY_ALERT_SND, "PlayAlertSound"},
	{E_PLAY_ALERT_POS, "PlayAlertSoundPositional"},
	{E_PLAY_EFFECT, "PlayEffect"},
	{E_SET_BG_COLOR, "SetBackgroundColor"},
	{E_SET_BORDER_COLOR, "SetBorderColor"},
	{E_SET_FONT_SIZE, "SetFontSize"},
	{E_SET_TEXT_COLOR, "SetTextColor"},
};

/**
 * TODO : There's deprecated set of Operators
 * with the exact same token but data is different.
 * E.g. token E_EQUAL with data "Equals".
 * Should it be supported? If so add it.
 */
const OperatorToken operator_tokens[] =
{
	{E_EQUAL, "="},
	{E_NOT_EQUAL, "!"},
	{E_LESS_THAN_EQUAL, "<="},
	{E_GREATER_THAN_EQUAL, ">="},
	{E_LESS_THAN, "<"},
	{E_GREATER_THAN, ">"},
	{E_EXACT, "=="},
};

const BlockToken block_tokens[] =
{
	{E_COMMENT, "#"},
	{E_SHOW, "Show"},
	{E_HIDE, "Hide"},
	{E_CONTINUE, "Continue"},
};

const ConditionToken* cond_token_get_by_str(char* data)
{
	const ConditionToken* tk;

	for (tk = condition_tokens; tk != NULL; tk++)
	{
		if (strcmp(tk->data, data) == 0)
		{
			return tk;
		}
	}

	return NULL;
}

const ActionToken* act_token_get_by_str(char* data)
{
	const ActionToken* tk;

	for (tk = action_tokens; tk != NULL; tk++)
	{
		if (strcmp(tk->data, data) == 0)
		{
			return tk;
		}
	}

	return NULL;
}

const OperatorToken* op_token_get_by_str(char* data)
{
	const OperatorToken* tk;

	for (tk = operator_tokens; tk != NULL; tk++)
	{
		if (strcmp(tk->data, data) == 0)
		{
			return tk;
		}
	}

	return NULL;
}

const BlockToken* blk_token_get_by_str(char* data)
{
	const BlockToken* tk;

	for (tk = block_tokens; tk != NULL; tk++)
	{
		if (strcmp(tk->data, data) == 0)
		{
			return tk;
		}
	}

	return NULL;
}


static Token* TokAlloc(const void* tok, TokenType type)
{
	Token* newToken = new Token;

	newToken->clas = tok;
	newToken->type = type;

	return newToken;
}

Token* TokGetToken(const char* data, size_t size)
{
	const void* clas;
	if ((clas = cond_token_get_by_str((char*)data)) != NULL)
	{
		// Create new Token object.

		return TokAlloc(clas, TK_CONDITION);
	}

	if ((clas = act_token_get_by_str((char*)data)) != NULL)
	{
		return TokAlloc(clas, TK_ACTION);
	}

	if ((clas = op_token_get_by_str((char*)data)) != NULL)
	{
		return TokAlloc(clas, TK_OPERATOR);
	}

	if ((clas = blk_token_get_by_str((char*)data)) != NULL)
	{
		return TokAlloc(clas, TK_BLOCK);
	}

	return NULL;
}
