#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "codec.h"




int alphanumeric_ind(char ch)
{
    /* Returns ind of charcter in the sorted alphanumeric alphabet. */

    if (ch == '0')   return codelen - 1;
    if (islower(ch)) return ch - 'a';
    if (isupper(ch)) return ch - 'A' + letter_count;
    if (isdigit(ch)) return ch - '1' + 2 * letter_count;

    return -1;
}

char alphanumeric_char(int ind)
{
    /* Returnsthe ind'th charcter in the sorted alphanumeric alphabet. */

    return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"[ind];
}


char * createCodec (char key[codelen])
{
    bool checks[codelen];
    int pa_ind, key_ind;

    for (key_ind = 0; key_ind < codelen; key_ind++)
    {
        pa_ind = alphanumeric_ind(key[key_ind]);

        // not alphanumeric or already apeared
        if (pa_ind == -1 || checks[pa_ind]) return NULL;

        checks[pa_ind] = true;
    }

    return key;
}


int encode(char * textin, char * textout, int len, char * codec)
{
    if (! textin || ! textout)
    {
        fprintf(stderr, "null text \n");
        return -1;
    }

    char ch;
    size_t ind;

    for (ind = 0; ind < len; ch = textin[ind++])
    {
        textout[ind] = isalnum(ch) ? codec[alphanumeric_ind(ch)] : ch;
    }

    return ind;
}



int decode(char * textin, char * textout, int len, char * codec)
{
    size_t ind;
    char reverse_codec[codelen] = (char * ) calloc(codelen, sizeof(char));

    for (ind = 0; ind < codelen; ind++)
    {
        reverse_codec[alphanumeric_ind(codec[ind])] = alphanumeric_char(ind);
    }
    
    return encode(textin, textout, len, reverse_codec);
}


void freecodec(char * codec)
{
    free(codec);
}