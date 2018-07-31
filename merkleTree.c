#include "md5.h"
#include <stdbool.h>
#include <math.h>

struct node {
    //store either filename (max 255 char) or hash (32 char)
    char *data;
    struct node *left;
    struct node *right;
};

struct node* newNode(const char *data) {
    // Allocate memory for new node
    struct node* node = (struct node*)malloc(sizeof(struct node));

    // Assign data to this node
    node->data = data;

    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;
    return(node);
}

int insertNode(struct node *head, const char *data, int maxDepth) {
    //do level order traversal until you find an empty space
    if (head->left == NULL && maxDepth != 0) {
        head->left = newNode(data);
        return 1;
    }
    else if (head->right == NULL && maxDepth != 0) {
        head->right = newNode(data);
        return 1;
    }
    else if (maxDepth == 0)
        return -1;
    else {
        if(insertNode(head->left, data, maxDepth - 1) == 1)
            return 1;
        if(insertNode(head->right, data, maxDepth - 1) == 1)
            return 1;
        return -1;
    }
}

char *hash(char * msg) {
    //function that uses md5(msg, len) and converts outputs to a single hash that's returned as a string
    size_t len = strlen(msg);
    //printf("\nstr: %c\n", msg[len+1]);
    //msg[len] = '\0';
    md5(msg, len);

    static char digest[33] = "";
    memset(digest,0,sizeof(digest));
    uint8_t *p;
    printf("\nDigest: %s\n", digest);
    // save result to digest
    p=(uint8_t *)&h0;
    sprintf(digest + strlen(digest), "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h1;
    sprintf(digest + strlen(digest), "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h2;
    sprintf(digest + strlen(digest), "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h3;
    sprintf(digest + strlen(digest), "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    //puts("");

    digest[32] = '\0';
    printf("\nMessage content:\n%s\n", msg);
    printf("\nDigest: %s\n", digest);
    return digest;
}

//fc = 11;
//p = 4; //2^4 = 16 leaves
//actual numNodes = 21
//calculated numNodes = 21
void printTree(struct node *head) {
    printf("\n1:%s\n2:%s\n3:%s\n4:%s\n5:%s\n6:%s\n7:%s\n8:%s\n9:%s\n",
           head->data,head->left->data,head->right->data,head->left->left->data, head->left->right->data,
           head->right->left->data, head->right->right->data, head->left->left->left->data,head->left->left->right->data);
}

void generateHashTree(struct node * head) {
    //printTree(head);
    //if head data isn't null, head already has hash and doesn't need to generate hash
    if (head->data != NULL) {
        printf("BOUNCE");
        return;
    }
    //if both left & right are null, you're at a leaf
    //if (head->left == NULL && head->right == NULL)
    //    return;
    //attempt to generate the hashes of the two children nodes of the head
    generateHashTree(head->left);
    generateHashTree(head->right);
    printf("BOUNCE BACK");
    //if both still null after trying, node is parent to 2 empty nodes
    //if (head->left->data == NULL && head->right->data == NULL)
    //    return;
    //if only one is still null, node is parent to a hash node and a non hash node
    if (head->left->data == NULL) {
        printf("LNULLSET");
        head->data = head->right->data;
        //head->data = hash(strcat(head->right->data, head->right->data));
    }
    else if (head->right->data == NULL) {
        printf("RNULLSET");
        head->data = head->left->data;
        //head->data = hash(strcat(head->left->data, head->left->data));
    }
    //if neither is null, node is parent to two hash nodes
    else {
        printf("HASHING");
        printf("\nL: %s", head->left->data);
        printf("\nR: %s", head->right->data);
        printf("LEFTRIGHT");
        char tmp[100] = "";
        strcat(tmp, head->left->data);
        strcat(tmp, head->right->data);
        head->data = hash(tmp);

        //head->data = hash(strcat(head->left->data, head->right->data));
        printf("FINISH HASHING");
        //strcpy(head->data, hash(strcat(head->left->data, head->right->data)));
        printf("PRINT STATEMENT: %s", head->data);
    }
}

void buildTree(const char *hashes[100], int fileCount) { // might replace filecount with array.length and hashes with arraylist
    //instantiate a new head node for the tree
    struct node *head = newNode(NULL);

    //find the smallest power of 2 >= fileCount or the lowest level in the tree
    int power = 0;
    while ((1 << power) <= fileCount) {
        power++;
    }

    //find the number of leaves at the power level and the power - 1 level
    //these are the only places they can be on a balanced binary tree
    //int x = 0, y = pow(2, power-1);
    int x = 0, y = (1 << (power - 1));
    int numNodes = 0;
    while (x <= (1 << (power-1)) && y >= 0) {
        if ((2 * x + y) != fileCount) {
            x++;
            y--;
        }
        else {
            numNodes = (1 << power) - 1 + 2 * x;
            break;
        }
    }
    printf("n%d x%d y%d", numNodes, x,y);
    printf("Leaves Calculated");
    //insert all blank nodes up to the power - 2 level
    for (int i = 1; i <= power - 2; i++)
        for (int j = 1; j <= (1 << power); j++)
            insertNode(head, NULL, i);
    printf("Insert 1");
    //insert final blank nodes on the power - 1 level
    for (int k = 1; k <= ((1 << (power-1)) - y); k++)
        insertNode(head, NULL, (power - 1));
    printf("Insert 2");
    //insert y hash nodes on the power - 1 level
    for (int n = 0; n < y; n++)
        insertNode(head, hashes[n], (power - 1));
    printf("Insert 3");
    //insert 2x hash nodes on the power level
    for (int m = 0; m < (2 * x); m++)
        insertNode(head, hashes[y + m], power);
    printf("Insert 4");
    //generateFinalHash(head);
    printTree(head);
    generateHashTree(head);
    printTree(head);
    printf("Final hash of tree is: %s\n", head->data);
}

//ins 2^p-1 max depth insert 2n max depth + 1

int main() {
    int choice, i = 0;
    char *fileData;
    char inputFileName[256];
    long inputFileSize;
    int fileCount = 0;
    struct node head;
    int power = 0;
    //figure out how to make this scaleable. arraylist?
    char *hashes[100];
    while (1) {
        printf("Enter your option:\n1. Add node to tree\n2. Generate final hash\n3. Wipe Tree\n4. Exit");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter the full path to the file you'd like to add:");
            scanf("%s",inputFileName);
            FILE *inputFile = fopen(inputFileName, "rb");
            fseek(inputFile, 0, SEEK_END);
            inputFileSize = ftell(inputFile);
            rewind(inputFile);
            fileData = malloc((inputFileSize + 1) * (sizeof(char)));
            fread(fileData, sizeof(char), inputFileSize, inputFile);
            fclose(inputFile);
            fileData[inputFileSize] = '\0';
            fileCount++;
            //file_contents = malloc((input_file_size + 1) * (sizeof(char)));
            //fread(file_contents, sizeof(char), input_file_size, input_file);
            //fclose(input_file);
            //file_contents[input_file_size] = 0;

            hashes[i] = malloc(sizeof(char*)*33);
            strcpy(hashes[i], hash(fileData));
            //hashes[i] = hash(fileData);
            printf("Hash: %s", hashes[i]);
            printf("\nAddress of string: %u", hashes[i]);
            printf("\nFilecount: %d\n\n", fileCount);
            i++;
        }
        else if (choice == 2) {
            /*
            struct node *headNode = newNode(NULL);
            //size_t numberLeaves = *(&fileData + 1) - fileData;
            //find n, the smallest power of 2 > fileCount
            printf("\nbefore power");
            while ((1 << power) < fileCount) {
                power++;
            }
            printf("\nafter power: %d", power);
            //fill tree with 2^(n+1)-1 non leaf nodes
            insertBlankNodes(headNode, power);
            printf("\ninsert blank successful");
            //insert hashes as bottom layer of nodes
            insertHashNodes(headNode, power, hashes, fileCount);
            printf("\ninsert hash successful");
            //generate hashes for tree
            generateHashTree(headNode);
            printf("\nfinal hash successful\n");
            printf("Final hash of tree is: %s", headNode->data);
            */
            printf("Start build");
            buildTree(hashes, fileCount);
            //exit(0);
        }
        else if (choice == 3) {
            //wipeTree();
        }
        else if (choice == 4) {
            return 0;
        }
        else {
            printf("Your choice is incorrect. Please try again.\n");
        }
    }
}


//have to recursively return a value to tell each recurse to either continue searching down other branch or terminate

/*
int insertHash(head, hash) {
//traverse down tree
if head == null
    return -1;
if head.left == null && head.right == null
    if head.data == null
    	head.data = hash;
	return 1;
    else
        return;
//if else if is important because you want to prefer left
if inserthash(head.left) == 1
	return 1
else if inserthash(head.right) == 1
	return 1
else
	return -1
}

int insertNode(struct node *head, const char *data, int maxDepth) {
    //do level order traversal until you find an empty space
    if (head->left == NULL && maxDepth != 0) {
        head->left = newNode(data);
        return 1;
    }
    else if (head->right == NULL && maxDepth != 0) {
        head->right = newNode(data);
        return 1;
    }
    else if (maxDepth == 0)
        return -1;
    else {
        if(insertNode(head->left, data, maxDepth - 1) == 1)
            return 1;
        if(insertNode(head->right, data, maxDepth - 1) == 1)
            return 1;
        return -1;
    }
}
*/

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

    printf("Digest: %s aaaa", digest);
    return 0;
}
*/
