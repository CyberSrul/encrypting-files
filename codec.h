#pragma once
#define letter_count 26
#define digit_count 10
#define codelen 62
#define alphabet "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"


char * createCodec (char[codelen]);
int encode(char *, char *, int, char *);
int decode(char *, char *, int, char *);
void freecodec(char *);