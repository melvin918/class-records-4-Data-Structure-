#ifndef BST_H
#define BST_H

typedef struct Node {
    void *data;
    struct Node* left;
    struct Node* right;
} Node;

Node *insertNode(Node *root, void *key, int (*cmp)(const void *a, const void *b)); 
Node *searchNode(Node *root, void *key, int (*cmp)(const void *a, const void *b)); 
Node *deleteNode(Node *root, void *key, int (*cmp)(const void *a, const void *b));
void freeTree(Node *root);

#endif // BST_H