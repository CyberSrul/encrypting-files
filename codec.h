#pragma once
#define letter_count 26
#define digit_count 10
#define codelen 62
#include <stdio.h>




char * createCodec (char[codelen]);
int encode(char *, char *, int, char *);
int decode(char *, char *, int, char *);
void freecodec(char *);
void ProccesFile(FILE *, FILE *, char *, bool);