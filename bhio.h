#ifndef BHIO_H
#define BHIO_H

#include <stdio.h>
#include <stdlib.h>

char* bh_reads() {
#define CHUNK 8
   char* input = NULL;
   char tempbuf[CHUNK];
   size_t inputlen = 0, templen = 0;
   do {
       fgets(tempbuf, CHUNK, stdin);
       templen = strlen(tempbuf);
       input = realloc(input, inputlen+templen+1);
       strcpy(input+inputlen, tempbuf);
       inputlen += templen;
    } while (templen==CHUNK-1 && tempbuf[CHUNK-2]!='\n');
    return input;
}
#undef CHUNK

#endif//BHIO_H