
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char g_node_error[128];

Block* CreateBlock(int type)
{
	Block* blk = (Block*)malloc(sizeof(Block));
	if (blk == NULL) {
		sprintf(g_node_error, "block_add() => Internal Memory error.\n");
		return NULL;
	}

	blk->type = type;

	return blk;
}

Prop* CreateProp(Block* blk, char* key)
{
	Prop* prop = (Prop*)malloc(sizeof(Prop));
	if (prop == NULL) {
		sprintf(g_node_error, "prop_add() => Internal Memory error.\n");
	}

	// prop->values = (Attr*)malloc(sizeof(Attr) * ATTR_LIST_MAX);

	blk->prop = prop;

	return prop;
}

Attr* CreateAttr(Prop* prp, char* data)
{
	Attr* attr = malloc(sizeof(Attr));

	if (attr == NULL) {
		sprintf(g_node_error, "attr_add() => Internal Memory error.\n");
		return NULL;
	}
	attr->data = data;

	InsertAttr(prp, attr);

	return attr;
}

//
// Free the given struct with it's dependencies?
// Reconsider the allocation strategy.
//

void FreeBlock(Block* blk)
{
	free(blk);
}

void FreeProp(Prop* prp)
{
	free(prp->attributes);
	free(prp);
}

void FreeAttr(Attr* attr)
{
	free(attr);
}



// Necessarily doesnt need the context object AS
// we can travel the chain from the root itself.
// Tho it can be a help if we require performance.
Node* AddNode(NodeContext* ctrl, Node* root, Block* data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		sprintf(g_node_error, "AddNode() => Failed to allocate new node.");
		return NULL;
	}

	// Implement the linked list object insert.
	// root->prev = node;

	return node;
}

void InsertAttr(Prop* prp, Attr* attr)
{
	/*if (prp->attributes ATTR_LIST_LEN) {
		sprintf(g_node_error, "InsertAttr() => List length exceeded.");
		return;
	}*/

	// Inserts the Attribute to the Property provided.
	// Copied to the list?
	//*(prp->attr_list + prp->attr_len) = attr;
	//prp->attr_len++;
}
