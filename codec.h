#pragma once
#define codelen 62



void * createCodec (char[codelen]);
int encode(char *, char *, int, void *);
int decode(char *, char *, int, void *);
void freecodec(void *); 