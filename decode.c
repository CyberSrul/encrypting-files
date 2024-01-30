#include <stdio.h>
#include <stdbool.h>
#include "codec.h"


int main(int argc, char const *argv[])
{
    // set up

    if (argc < 3) return throw("expecting src and dst files");

    FILE * src = fopen(argv[1], "rb");
    FILE * dst = fopen(argv[2], "wb");

    if (! src || ! dst) return throw("can not open files");

    char code[codelen];
    printf("Please enter a substatution decryption key: \n");
    scanf(" %s", code);
    
    if (! createCodec(code)) return throw("Invalid key");


    // encrypting file

    ProccesFile(src, dst, code, false);

    fclose(src);
    fclose(dst);
    return EXIT_SUCCESS;
}