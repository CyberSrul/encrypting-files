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
    /* Returns ind-th char in the sorted alphanumeric alphabet. */

    if (ind < 0 || ind >= codelen) return -1;
    if (ind < letter_count)        return 'a' + ind;
    if (ind < 2 * letter_count)    return 'A' + ind - letter_count;
    if (ind == codelen - 1)        return '0';

    return '1' + ind - 2 * letter_count;
}


char * createCodec (char key[codelen])
{
    bool checks[codelen] = {0};
    int pa_ind, key_ind;

    for (key_ind = 0; key_ind < codelen; key_ind++)
    {
        pa_ind = alphanumeric_ind(key[key_ind]);

        // too short code, not alphanumeric, char apeared twice
        if (! key[key_ind] || pa_ind == -1 || checks[pa_ind]) return NULL;

        checks[pa_ind] = true;
    }

    return key;
}


void freecodec(char * codec)
{
    free(codec);
}


int encode(char * textin, char * textout, int len, char * codec)
{
    if (! textin || ! textout || ! codec)
    {
        fprintf(stderr, "null text \n");
        return -1;
    }

    char ch = textin[0];
    size_t ind;

    for (ind = 0; ind < len; ch = textin[++ind])
    {
        textout[ind] = isalnum(ch) ? codec[alphanumeric_ind(ch)] : ch;
    }

    return ind;
}


void reverseCodec(char * codec, char * revcodec)
{
    for (size_t ind = 0; ind < codelen; ind++)
    {
        revcodec[alphanumeric_ind(codec[ind])] = alphanumeric_char(ind);
    }
}


int decode(char * textin, char * textout, int len, char * codec)
{
    static char revcodec[codelen] = {0}, * prevcodec = NULL;

    if (codec != prevcodec)
    {
        reverseCodec(codec, revcodec);
        prevcodec = codec;
    }
    
    return encode(textin, textout, len, revcodec);
}


void ProccesFile(FILE * src, FILE * dst, char * codec, bool encrypt)
{
    if (! src || ! dst)
    {
        fprintf(stderr, "null file \n");
        exit(EXIT_FAILURE);
    }

    const unsigned int bufflen = 1000;
    char buffer[1000] = {0};
    int bytes_read;

    int ( * method)(char *, char *, int, char *) = (encrypt ? encode : decode);

    while (0 < (bytes_read = fread(buffer, sizeof(char), bufflen, src)))
    {
        method(buffer, buffer, bufflen, codec);

        fwrite(buffer, sizeof(char), bytes_read, dst);
    }
} 