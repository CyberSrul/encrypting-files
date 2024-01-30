#pragma once
#include <stdio.h>
#include <stdlib.h>
#define letter_count 26
#define digit_count 10
#define codelen 62
#define bufflen 1000




char * createCodec (char[codelen]);
int encode(char *, char *, int, char *);
int decode(char *, char *, int, char *);
void freecodec(char *);
void ProccesFile(FILE *, FILE *, char *, bool);


static int throw(char * msg)
{
    fprintf(stderr, "%s \n", msg);
    return EXIT_FAILURE;
}