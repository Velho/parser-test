#pragma once

struct _Token;

typedef struct {
	struct _Token* token;
	// Token data can be either TokenData or TokenValue.
	void* data;
} SemClas;

SemClas* SAGetInst(void* data, struct _Token* tok);

void SemInit();
void SemRelease();

SemClas* SemAssignToken(struct _Token* tok_clas, void* data);

