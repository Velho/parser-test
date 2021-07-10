#pragma once

// Tokenizer interface.

//
// Token interface shouldn't take syntax
// into consideration ==>
// ConditionTokens is described as 'Conditions'
// and there is the Actions as well.
// Actions modify the color, icons, visual effects and sounds.
//

#define DEF_TOKEN_CLASS(clas, tokens)	\
	typedef struct {					\
		tokens token; 					\
		char* data;						\
	} clas;


typedef enum {
	E_NONE,
	E_ALTQUAL, 		//! AlternateQuality
	E_ANYENCH, 		//! AnyEnchantment
	E_AREALVL, 		//! AreaLevel
	E_BASETYPE,		//! BaseType
	E_BLIGHTMAP, 	//! BlightedMap
	E_CLASS, 		//! Class
	E_CORRUPTED, 	//! Corrupted
	E_CORRUPTEDMOD,	//! CorruptedMods
	E_DROPLVL, 		//! DropLevel
	E_ELDERITEM,	//! ElderItem
	E_ELDERMAP,		//! ElderMap
	E_ENCHPASSNODE,	//! EnchantmentPassiveNode
	E_ENCHPASSNUM,	//! EnchantmentPassiveNum
	E_FRACTITEM,	//! FracturedItem
	E_GEMLEVEL,		//! GemLevel
	E_GEMQUALTYPE,	//! GemQualityType
	E_HASENCH,		//! HasEnchantment
	E_HASEXPLMOD,	//! HasExplicitMod
	E_HASINFL,		//! HasInfluence
	E_HEIGHT,		//! Height
	E_IDENTIFIED,	//! Identified
	E_ITEMLVL,		//! ItemLevel
	E_LINKEDSOCKETS,//! LinkedSockets
	E_MAPTIER,		//! MapTier
	E_MIRRORED,		//! Mirrored
	E_PROPHECY,		//! Prophecy
	E_QUALITY,		//! Quality
	E_RARITY,		//! Rarity
	E_REPLICA,		//! Replica
	E_SHAPEDMAP,	//! ShapedMap
	E_SHAPERITEM,	//! ShaperItem
	E_SOCKETGROUP,	//! SocketGroup
	E_SOCKETS,		//! Sockets
	E_STACKSIZE,	//! StackSize
	E_SYNTHITEM,	//! SynthesisedItem
	E_WIDTH,		//! Width
} ConditionTokens;

typedef enum {
	E_COMMENT,
	E_SHOW,
	E_HIDE,
	E_CONTINUE
} BlockTokens;

typedef enum {
	E_CUSTOM_ALERT_SND,
	E_DISABLE_DROP_SND,
	E_ENABLE_DROP_SND,
	E_MINIMAPICON,
	E_PLAY_ALERT_SND,
	E_PLAY_ALERT_POS,
	E_PLAY_EFFECT,
	E_SET_BG_COLOR,
	E_SET_BORDER_COLOR,
	E_SET_FONT_SIZE,
	E_SET_TEXT_COLOR,
} ActionTokens;

typedef enum {
	E_EQUAL,
	E_NOT_EQUAL,
	E_LESS_THAN_EQUAL,
	E_GREATER_THAN_EQUAL,
	E_LESS_THAN,
	E_GREATER_THAN,
	E_EXACT
} OperatorTokens;

DEF_TOKEN_CLASS(ConditionToken, ConditionTokens);
DEF_TOKEN_CLASS(ActionToken, ActionTokens);
DEF_TOKEN_CLASS(OperatorToken, OperatorTokens);
DEF_TOKEN_CLASS(BlockToken, BlockTokens);

ConditionToken* cond_token_get_by_str(char* data);
ActionToken* act_token_get_by_str(char* data);
OperatorToken* op_token_get_by_str(char* data);
BlockToken* blk_token_get_by_str(char* data);

typedef union {
	ConditionToken ctoken;
	ActionToken atoken;
	OperatorToken otoken;
	BlockToken btoken;
} MyUnion;

typedef struct {
	void* token;

	enum {
		TK_CONDITION,
		TK_ACTION,
		TK_OPERATOR,
		TK_BLOCK
	} token_type;
} Token;

//
// Support functions for the Token Class identifying,
// 
//

