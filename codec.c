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
        revcodec[alphanumeric_ind(codec[ind])] = alphabet[ind];
    }
}


int decode(char * textin, char * textout, int len, char * codec)
{
    static char revcodec[codelen] = {0};
    static char * prevcodec = NULL;
    if (codec != prevcodec) reverseCodec(codec, revcodec);
    
    return encode(textin, textout, len, revcodec);
}


void ProccesFile(FILE * src, FILE * dst, char * codec, bool encrypt)
{
    if (! src || ! dst)
    {
        fprintf(stderr, "null file \n");
        exit(EXIT_FAILURE);
    }

    int ( * TextProcceser)(char *, char *, int, char *) = (encrypt ? encode : decode);
    const unsigned int bufflen = 1000;
    char buffer[1000] = {0};
    int bytes_read;

    while (0 < (bytes_read = fread(buffer, sizeof(char), bufflen, src)))
    {
        TextProcceser(buffer, buffer, bufflen, codec);

        fwrite(buffer, sizeof(char), bytes_read, dst);
    }
} 