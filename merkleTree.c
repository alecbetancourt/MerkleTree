#include "md5.h"
#include <stdbool.h>

/*
int main() {
    //ask how many data blocks
    //make method to find tree height n (such that 2^n > |data blocks|)
    //construct bulk of tree using 'hash nodes' - build head and then add 2^(n+1)-1 hash nodes
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

struct node
{
    //store either filename (max 255 char) or hash (32 char)
    char *data;
    struct node *left;
    struct node *right;
};

struct node* newNode(char *data)
{
    // Allocate memory for new node
    struct node* node = (struct node*)malloc(sizeof(struct node));

    // Assign data to this node
    node->data = data;

    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;
    return(node);
}

void addNode() {

}

void insertBlankNodes(int nower) {

}

void insertHashNodes(int fileCount) { //also pass array/arraylist of hashes as parameter

}

char * generateFinalHash() {
    char finalHash[33];
    //get final hash and return as string
}

int main() {
    bool menu = true;
    int choice, i = 0;
    char *fileData;
    char inputFileName[256];
    long inputFileSize;
    int fileCount = 0;
    struct node head;
    int power = 0;

    while (menu) {
        printf("Enter your option:\n1. Add node to tree\n2. Generate final hash\n3. Wipe Tree\n4. Exit");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter the path to the file you'd like to add:");
            scanf("%s",inputFileName);
            FILE *inputFile = fopen(inputFileName, "rb");
            fseek(inputFile, 0, SEEK_END);
            inputFileSize = ftell(inputFile);
            rewind(inputFile);
            fileData = malloc(inputFileSize * (sizeof(char)));
            fread(fileData, sizeof(char), inputFileSize, inputFile);
            fclose(inputFile);
            fileCount++;
            //file_contents = malloc((input_file_size + 1) * (sizeof(char)));
            //fread(file_contents, sizeof(char), input_file_size, input_file);
            //fclose(input_file);
            //file_contents[input_file_size] = 0;
        }
        else if (choice == 2) {
            size_t numberLeaves = *(&fileData + 1) - fileData;
            //find n, the smallest power of 2 > numberLeaves
            while (2^power < fileCount) {
                power++;
            }
            //fill tree with 2^(n+1)-1 non leaf nodes
            insertBlankNodes(power);
            //insert hashes as bottom layer of nodes
            //insertHashNodes(fileCount, list);
            printf("Final hash of tree is: %s", generateFinalHash());
        }
        else if (choice == 3) {
            //wipeTree();
        }
        else if (choice == 4) {
            //delete later
            menu = false;
            //return 0;
        }
        else {
            printf("Your choice is incorrect. Please try again.");
        }
    }

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