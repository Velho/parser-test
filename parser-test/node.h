#pragma once

#include "token.h"

//
// Disable Security warnings.
// Shouldnt be the default option.
//
#define _CRT_SECURE_NO_WARNINGS

#define ATTR_LIST_LEN	24

/**
 * Memory pool functions are not implemented,
 * Custom memory management functions for allocations,
 * deallocs, etc.
 */

typedef struct {
	char* data;
} Attr;

typedef Attr* AttributeList;

typedef struct {
	char* key;

	int attr_len;
	AttributeList attr_list[ATTR_LIST_LEN]; // Array of Attributes.
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
Block* block_add(int type);
Prop* prop_add(Block* blk, char* key);
Attr* attr_add(Prop* prp, char* data);

void free_block(Block* blk);
void free_prop(Prop* prp);
void free_attr(Attr* attr);

const char* get_last_error();