
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ATTR_LIST_MAX	24

char* g_error[128];

Block* CreateBlock(int type)
{
	Block* blk = (Block*)malloc(sizeof(Block));
	if (blk == NULL) {
		sprintf(g_error, "CreateBlock() => Internal Memory error.\n");
		return NULL;
	}

	blk->type = type;

	return blk;
}

Prop* CreatePro(Block* blk, char* key)
{
	Prop* prop = (Prop*)malloc(sizeof(Prop));
	if (prop == NULL) {
		sprintf(g_error, "CreatePro() => Internal Memory error.\n");
		return NULL;
	}

	prop->key = key;
	
	// Allocate max amount of attributes.
	prop->attr_len = 0;
	prop->values = (Attr*)malloc(sizeof(Attr) * ATTR_LIST_MAX);

	blk->prop = prop;

	return prop;
}

Attr* CreateAttr(Prop* prp, char* value)
{
	Attr* attr = malloc(sizeof(Attr));
	if (attr == NULL) {
		sprintf(g_error, "CreateAttr() => Internal Memory error.\n");
		return NULL;
	}
	attr->value = value;

	InsertAttr(prp, attr);

	return attr;
}

void FreeBlock(Block* blk)
{
	free(blk);
}

void FreePro(Prop* prp)
{
	free(prp->values);
	free(prp);
}

void FreeAttr(Attr* attr)
{
	free(attr);
}

const char* GetLastError()
{
	return g_error;
}

Node* AddNode(Node* root, Type* value)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		sprintf("AddNode() => Failed to allocate new node.");
	}

	node->value = value;
	root->prev = node;

	return node;
}

void InsertAttr(Prop* prp, Attr* attr)
{
	// Inserts the Attribute to the Property provided.
	// Copied to the list?
	prp->values = attr;
	prp->attr_len++;
}
