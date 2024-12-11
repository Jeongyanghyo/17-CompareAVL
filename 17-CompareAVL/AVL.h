#pragma once

typedef struct Node {
    int key;
    struct Node* left, * right;
    int height;
} Node;

extern Node* insertNode(Node* root, int key);
extern Node* deleteNode(Node* root, int key);
extern Node* searchNode(Node* root, int key);
extern void inOrder(Node* root);
extern void freeTree(Node* root);
extern void doAVLBatch(Node* root);
extern void doBinaryBatch(Node* root);

extern int compareCount;
extern int searchCount;

