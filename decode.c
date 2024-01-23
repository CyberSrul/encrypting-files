#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "codec.h"


int main(int argc, char const *argv[])
{
    char * code = createCodec("abcdrEFGHIJKLMhijklmnopqNOPQRsxyzABCDSvwfgXY789Z12TUVWetu34560");
    
    FILE * src = fopen("encrypted.txt", "rb");
    FILE * dst = fopen("decrypted.txt", "wb");

    ProccesFile(src, dst, code, false);

    fclose(src);
    fclose(dst);
    return EXIT_SUCCESS;
}