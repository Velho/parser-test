#pragma once

/**
 * Memory pool functions are not implemented,
 * Custom memory management functions for allocations,
 * deallocs, etc.
 */

typedef struct {
	char* value;
} Attr;

typedef struct {
	char* key;

	int attr_len;
	Attr* values; // Array of Attributes.
} Prop;

typedef struct {
	int type;
	Prop* prop; // Array of properties.
} Block;

typedef struct {
	enum {
		T_ATTR,
		T_PROP,
		T_BLOCK
	} eType;

	union {
		Attr a;
		Prop p;
		Block b;
	} value;

} Type;

typedef struct {
	struct Node* next;
	struct Node* prev;

	Type* value;
} Node;

// Node root;

//
// Node management.
// Nodes inserted from left-to-right.
//
Node* AddNode(Node* root, Type* value);

/**
 * Inserts attribute 
 */
void InsertAttr(Prop* prp, Attr *attr);

//
// Struct allocation functions.
//
Block* CreateBlock(int type);
Prop* CreatePro(Block* blk, char* key);
Attr* CreateAttr(Prop* prp, char* value);

void FreeBlock(Block* blk);
void FreePro(Prop* prp);
void FreeAttr(Attr* attr);

const char* GetLastError();