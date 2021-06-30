#pragma once


//
// Disable Security warnings.
// Shouldnt be the default option.
//
#define _CRT_SECURE_NO_WARNINGS

#define ATTR_LIST_LEN	24

/**
 * deallocs, etc.
 */

typedef struct {
	char* data;
} Attr;

typedef Attr** AttributeList;

typedef struct {
	AttributeList attributes; // Array of Attributes.
} Prop;

typedef struct {
	int type;
	Prop* prop; // Array of properties.
} Block;


//! Linked-List as Block container.
typedef struct {
	struct Node* next;
	struct Node* prev;

	Block* data;
} Node;


typedef struct {
	Node* head;
	Node* current;

	char error[128];
} NodeContext;

// Node root;

//
// Node management.
// Nodes inserted from left-to-right.
//
// Node* AddNode(Node* root, Type* value);
Node* AddNode(NodeContext* ctrl, Node* root, Block* data);


/**
 * Inserts attribute 
 */
void InsertAttr(Prop* prp, Attr* attr);

//
// Struct allocation functions.
//
Block* CreateBlock(int type);
Prop* CreateProp(Block* blk, char* key);
Attr* CreateAttr(Prop* prp, char* data);
void FreeBlock(Block* blk);
void FreeProp(Prop* prp);
void FreeAttr(Attr* attr);

const char* GetLastError();
