#include "md5.h"
#include <stdbool.h>
#include <string.h>


struct node
{
    //store either filename (max 255 char) or hash (32 char)
    char *data;
    char *hashvalue;
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


insertNode(struct node head, char* data, int maxDepth) {
    //do level order traversal until you find an empty space
    //if head->left == null && maxDepth != 0
        //head left = newNode(data)
    //else if head->right == null && maxDepth != 0
        //head right = newNode(data)
    //else
        //insertNode(head->left, data, maxDepth - 1)
        //insertNode(head->right, data, maxDepth - 1)
}

void insertBlankNodes(struct node head, int nower) {
    //for (int i = 0; i < 2^(power+1)-1; i++)
    //insertNode(head, NULL, power)
}

void insertHashNodes(struct node head, int power) { //also pass array/arraylist of hashes as parameter; change fileCount to hashArray.length()
    //for (int i = 0; i < fileCount; i++)
    //insertNode(head, hashArray[i], power + 1)
}

char * hashNode(char * msg, struct node* n) {
    //function that uses md5(msg, len) and converts outputs to a single hash that's returned as a string
    size_t len = strlen(msg);
    md5(msg, len);

    char digest[100];
    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    uint8_t *p;

    // display result
    p=(uint8_t *)&h0;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
    sprintf(digest + strlen(digest), "-%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h0);
    //sprintf(digest + strlen(digest), "%x", *p);

    p=(uint8_t *)&h1;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);
    sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h1);

    p=(uint8_t *)&h2;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);
    sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h2);

    p=(uint8_t *)&h3;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);
    sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x", p[0], p[1], p[2], p[3], h3);
    //puts("");

    //printf("%s", digest);

    n->hashvalue=digest;
    n->data=digest;

}
/******
* Goal is to recursively build the tree from the leaves to the root.
*
******/
void generateHashTree(struct node* arr[], int size) {
    //if left->data == null
    //generateFinalHash(head->left)
    //if right->data == null
    //generateFinalHash(head->right)
    //else
    //head->data = hash(left->data+right->data))
    int nextLayercount=0;
    int index=0, ind=0;
    struct node* currLayer[5000]={NULL};
    if (size==1)
    {
        ;
    }
    else
    {
        if (size%2==0) //Determine if there are an odd number of nodes on the passed layer
    {
        nextLayercount=size/2;
    }
    else
    {
        nextLayercount=(size/2)+1;
    }
    while (index<=nextLayercount)
    {
        struct node* first= arr[index];
        struct node* second= arr[index];

        currLayer[ind]=newNode(strcat(first->data,second->data));

        struct node* here=currLayer[ind];
        here->left=arr[index];
        if ((index+1)<=size) //in case of odd sized trees
        {
            here->right=arr[index+1];
        }
        hashNode(here->data,here);
        index+=2;
        ind++;
    }
    generateHashTree(currLayer,ind); //recursive tree building
    }
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
    struct node *arr[5000]={NULL}; //Holds an array of pointers to nodes;
    int index=0;

    while (menu) {
        printf("Enter your option:\n1. Add node to tree\n2. Generate final hash\n3. Wipe Tree\n4. Exit\n");
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

            arr[index]=newNode(fileData);
            index++;
            //file_contents = malloc((input_file_size + 1) * (sizeof(char)));
            //fread(file_contents, sizeof(char), input_file_size, input_file);
            //fclose(input_file);
            //file_contents[input_file_size] = 0;

            //dataList[i] = hash(fileData, length)
            //i++
        }
        else if (choice == 2) {
            //struct node head = newNode(NULL);
            //size_t numberLeaves = *(&fileData + 1) - fileData;
            //find n, the smallest power of 2 > fileCount
            while (2^power < fileCount) {
                power++;
            }
            //fill tree with 2^(n+1)-1 non leaf nodes
            //insertBlankNodes(head, power);
            //insert hashes as bottom layer of nodes
            //insertHashNodes(head, power, list);
            //generateHashTree(head)
            //printf("Final hash of t0ree is: %s", head->data);
        }
        else if (choice == 3) {
            //wipeTree();
        }
        else if (choice == 4) {
            //delete later
            menu = false;
            exit(0);
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

    char digest[100] = "";
    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    uint8_t *p;

    // display result
    p=(uint8_t *)&h0;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
    //sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h0);
    //sprintf(digest + strlen(digest), "%x", *p);

    p=(uint8_t *)&h1;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);
    //sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h1);

    p=(uint8_t *)&h2;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);
    //sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x -", p[0], p[1], p[2], p[3], h2);

    p=(uint8_t *)&h3;
    //printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);
    //sprintf(digest + strlen(digest), "%2.2x - %2.2x - %2.2x - %2.2x", p[0], p[1], p[2], p[3], h3);
    //puts("");

    printf("Digest: %s aaaa", digest);
    return 0;
}
