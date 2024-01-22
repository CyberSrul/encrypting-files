#include <stdio.h>
#include "codec.h"


int main(int argc, char const *argv[])
{
    char * code = createCodec("abcdrEFGHIJKLMetuvwfghijklmnopqNOPQRsxyzABCDSTUVWXY789Z1234560");
    char txt1[] = "Hello there", txt2[12];
    encode(txt1, txt2, 12, code);
    printf("%s \n", txt2);
    decode(txt2, txt1, 12, code);
    printf("%s \n", txt1);
    

    return 0;
}