#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
// #include "string.h"
#include <stdlib.h>
// #include <errno.h>
#pragma GCC optimize("O3")
#define MEM_TO_READ 1024*1024*200

long long somma(FILE *f) {
    int offset = 0;
    char *pos = (char *) mmap(NULL, MEM_TO_READ, PROT_READ, MAP_PRIVATE, fileno(f), offset);
    char *starting = pos;

    int n = 0;
    for (; *pos != '\n'; pos++) {
        n = n * 10 + *pos - '0';
    }
    pos++;
    long long s = 0;

    while (n--) {
        int v = 0;
        char minus = 0;
        if (*pos == '-') {
            minus = 1;
            pos++;
        }
        for (; *pos >= '0'; pos++) {
            v = v * 10 + *pos - '0';
        }
        pos++;
        if (minus) {
            s-= v;
        }
        else {
            s+= v;
        }

        if (pos - starting > MEM_TO_READ - 50) {
            // read some more data
            offset+= pos - starting;
            int pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
            // printf("read %d, reading some more from %d...\n", offset, pa_offset);
            // for (int i = 0; i < 50; i++) {
            //     printf("%c", *(pos + i));
            // }
            // printf("\n");
            munmap(starting, MEM_TO_READ);
            pos = (char *) mmap(NULL, MEM_TO_READ, PROT_READ, MAP_PRIVATE, fileno(f), pa_offset);
            starting = pos;
            // printf("after\n");
            // for (int i = 0; i < 50; i++) {
            //     printf("%c", *(pos + i));
            // }
            pos+= offset - pa_offset;
            offset-= offset - pa_offset;
            // printf("after\n");
            // for (int i = 0; i < 50; i++) {
            //     printf("%c", *(pos + i));
            // }
            // printf("\n");
            // printf("keep on going... %p\n", pos);
        }
        // else if (offset > 419422200) {
        //     printf("missing %d", n);
        //     for (int i = 0; i < 10; i++)
        //         printf("%c", *(pos + i));
        //     printf("\t");
        // }
    }
    
    return s;
}
