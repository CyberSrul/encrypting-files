#pragma once
#define codelen 62
#define letter_count 26
#define digit_count 10


char * createCodec (char[codelen]);
int encode(char *, char *, int, char *);
int decode(char *, char *, int, char *);
void freecodec(char *); 