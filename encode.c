#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "codec.h"


int main(int argc, char const *argv[])
{
    char * code = createCodec("abcdrEFGHIJKLMhijklmnopqNOPQRsxyzABCDSvwfgXY789Z12TUVWetu34560");
    
    FILE * src = fopen("test.txt", "rb");
    FILE * dst = fopen("encrypted.txt", "wb");

    ProccesFile(src, dst, code, true);

    fclose(src);
    fclose(dst);
    return EXIT_SUCCESS;
}