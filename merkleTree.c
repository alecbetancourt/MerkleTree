#include "md5.h"

/*
int main() {
    //ask how many data blocks
    //make method to find tree height n (such that 2^n > |data blocks|)
    //construct bulk of tree using 'hash nodes' - build head and then add 2^(n-1)-1 hash nodes
    //make final layer data nodes - add #data blocks nodes based on user input
    //hash nodes: contain hash and children
    //data nodes: contain file names and children
    //write recursive function to compute hash of tree, if both children of a node are null, set node to null
    //if only one child is null, set parent to the hash of the non null child concatenated with a copy of itself
    //print tree hash to user

    char string[] = "string";
    char *argc = string[1];


    if (argc < 2) {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }

    char *msg = argv[1];
    size_t len = strlen(msg);

    // benchmark
    // int i;
    // for (i = 0; i < 1000000; i++) {
    md5(msg, len);
    // }

    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    uint8_t *p;

    // display result

    p=(uint8_t *)&h0;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);

    p=(uint8_t *)&h1;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);

    p=(uint8_t *)&h2;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);

    p=(uint8_t *)&h3;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);
    puts("");

    return 0;
}
*/

int main() {

    char string[] = "string";
    printf("\nString being hashed: %s\n\n",string);

    char *msg = string;
    size_t len = strlen(msg);

    // benchmark
    // int i;
    // for (i = 0; i < 1000000; i++) {
    md5(msg, len);
    // }
    
    char digest[100];
    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    uint8_t *p;

    // display result
    p=(uint8_t *)&h0;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
    sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h0);
    //sprintf(digest + strlen(digest), "%x", *p);

    p=(uint8_t *)&h1;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);
    sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h1);

    p=(uint8_t *)&h2;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);
    sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h2);

    p=(uint8_t *)&h3;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);
    sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x", p[0], p[1], p[2], p[3], h3);
    puts("");

    printf("%s", digest);
    return 0;
}