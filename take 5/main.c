#include <stdio.h>
#include <stdlib.h>
#include "md5.h"
#include <stdbool.h>
#include <string.h>

#define SIZE 5000000
char *files[51]={
    "1.txt",
    "2.txt",
    "3.txt",
    "4.txt",
    "5.txt",
    "6.txt",
    "7.txt",
    "8.txt",
    "9.txt",
    "10.txt",
    "11.txt",
    "12.txt",
    "13.txt",
    "14.txt",
    "15.txt",
    "16.txt",
    "17.txt",
    "18.txt",
    "19.txt",
    "20.txt",
    "21.txt",
    "22.txt",
    "23.txt",
    "24.txt",
    "25.txt",
    "26.txt",
    "27.txt",
    "28.txt",
    "29.txt",
    "30.txt",
    "31.txt",
    "32.txt",
    "33.txt",
    "34.txt",
    "35.txt",
    "36.txt",
    "37.txt",
    "38.txt",
    "39.txt",
    "40.txt",
    "41.txt",
    "42.txt",
    "43.txt",
    "44.txt",
    "45.txt",
    "46.txt",
    "47.txt",
    "48.txt",
    "49.txt",
    "50.txt",
};
void addNode(char *);
void removemNode();
void display();

char  items[SIZE][100];
int front = -1, rear = -1;

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

char * hashNode(char * msg) {
    //function that uses md5(msg, len) and converts outputs to a single hash that's returned as a string
       size_t len = strlen(msg);
    //printf("\nstr: %c\n", msg[len+1]);
    //msg[len] = '\0';
    md5(msg, len);

    static char digest[33] = "";
    memset(digest,0,sizeof(digest));
    uint8_t *p;
    // save result to digest
    p=(uint8_t *)&h0;
    sprintf(digest + strlen(digest), "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h1;
    sprintf(digest + strlen(digest), "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h2;
    sprintf(digest + strlen(digest), "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h3;
    sprintf(digest + strlen(digest), "%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);


    digest[32] = '\0';

    return digest;
}
/******
* A queue... to simulate a tree
*
******/
int generateHashTree() {
    char * temp1;
    char * temp2;
    char  temp3[100];
    if (rear-front==0)
    {
        printf("\nFinal hash: %s\n",items[front]);
        return 0;
    }
    else{
        temp1=items[front];
        removeNode();
        temp2=items[front];
        removeNode();
        strcpy(temp3,strcat(temp1,temp2));
        addNode(hashNode(temp3));
        generateHashTree();
    }

}


int main()
{
   bool menu = true;
    int choice, i = 0;
    char *fileData;
    char inputFileName[256];
    long inputFileSize=0;
    int fileCount = 0;
    struct node *arr[5000]={NULL}; //Holds an array of pointers to nodes;
    int index=0;
    int count=0;

    while (menu) {
        printf("\nEnter your option:\n1. Add nodes\n2. Generate final hash\n3. display\n4. Exit\n");
        scanf("%d", &choice);
        if (choice == 1) {
            while (count<50)
            {
            strcpy(inputFileName,files[count]);

            FILE *inputFile = fopen(inputFileName, "rb");
            fseek(inputFile, 0, SEEK_END);
            inputFileSize = ftell(inputFile);
            rewind(inputFile);
            fileData = malloc(inputFileSize * (sizeof(char)));
            fread(fileData, sizeof(char), inputFileSize, inputFile);
            fclose(inputFile);
            fileData[inputFileSize] = '\0';
            fileCount++;

            addNode(hashNode(fileData));
            index++;
            count++;
            }
        }
        else if (choice == 2) {
                generateHashTree(arr,fileCount);
        }
        else if (choice == 3) {
            display();
        }
        else if (choice == 4) {
            menu = false;
            exit(0);
        }
        else {
            printf("Your choice is incorrect. Please try again.");
        }
    }

    return 0;
}
void addNode(char * hash){
    if(rear == SIZE-1)
        printf("\nToo many nodes");
    else {
        if(front == -1)
            front = 0;
        rear++;
        strcpy(items[rear],hash);
    }
}

void removeNode(){
    if(front == -1)
        printf("\nNo nodes found");
    else{
        front++;
        if(front > rear)
            front = rear = -1;
    }
}

void display(){
    if(rear == -1)
        printf("\nThere is nothing to display");
    else{
        int i=0;
        printf("\Nodes\n");
        for(i=front; i<=rear; i++)
            printf("\n%s",items[i]);
    }
}

