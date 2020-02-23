#include "utils.h"

#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "log.h"

#define mem_error() \
    { ELOG("{!} Unexpected Memory error"); exit(EFAULT); }



void * umalloc(size_t size) {
    void * ptr;
    if ( (ptr = malloc(size)) )  return ptr;
    else mem_error();

    /*unreachable*/
    return NULL;
}

void * ucalloc(uint32_t qnt, size_t size) {
    void * ptr;
    if ( (ptr = calloc(qnt, size)) )  return ptr;
    else mem_error();

    return NULL;
}

char * strndup(const char *s, size_t n) {
    char *p = memchr(s, '\0', n);
    if (p != NULL)
        n = p - s;
    p = malloc(n + 1);
    if (p != NULL) {
        memcpy(p, s, n);
        p[n] = '\0';
    }
    return p;
}

long getncolor(const char * hex, int n) {
	long ulhex;
    /* base color lenght, without `#` (only rgb or rrggbb) */
    uint8_t lhex;


    ulhex = 0;
    lhex = n-1;

    /* invalid color */
    if (hex[0] != '#' || (lhex != 3 && lhex != 6)) return 0;

    char hex_group[7];
    hex++;

    /* handle colors in #rgb format */
    if (lhex == 3){
        hex_group[0] = hex_group[1] = hex[0]; /*r*/
        hex_group[2] = hex_group[3] = hex[1]; /*g*/
        hex_group[4] = hex_group[5] = hex[2]; /*b*/
    } else {
        /* handle colors in #rrggbb format */
        strncpy(hex_group, hex, 6);
    }

    //todo: check if the conversion was successful
    return (ulhex | strtol(hex_group, NULL, 16));
}