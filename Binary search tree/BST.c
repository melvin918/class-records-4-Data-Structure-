#include"BST.h"
#include <stdio.h>
#include <stdlib.h>

static Node *createNode(void *key){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> data = key;
    return newNode;
}

//cmp -1  data > root 
//     0  data = root
//     1  data < root
Node *insertNode(Node *root, void *key, int (*cmp)(const void *, const void *)){
    if (!root) return createNode(key);
    if (cmp(root -> data, key) == 0) 
        return root;
    else if (cmp(root -> data, key) == 1) 
        root -> left = insertNode(root -> left, key, cmp);   
    else 
        root -> right = insertNode(root -> right, key, cmp);
    return root;
} 

Node *searchNode(Node *root, void *key, int (*cmp)(const void *, const void *)){
    if (!root) return NULL;
    if (cmp(root -> data, key) == 0) 
        return root;
    if (cmp(root -> data, key) == 1)
        return searchNode(root -> left, key, cmp);
    return searchNode(root -> right, key, cmp);
}

Node *deleteNode(Node *root, void *key, int (*cmp)(const void *, const void *)){
    if (!root) return NULL;
    if (cmp(root -> data, key) == 1) 
        root -> left = deleteNode(root -> left, key, cmp);
    else if (cmp(root -> data, key) == -1) 
        root -> right = deleteNode(root -> right, key, cmp);
    else {
        if (!root -> left && !root -> right){
            free(root);
            return NULL;
        }
        if (!root -> left) {
            Node *temp = root -> right;
            free(root);
            return temp;
        }
        if (!root -> right) {
            Node *temp = root -> left;
            free(root);
            return temp;
        }
        Node *rightMin = root -> right;
        while (rightMin -> left) {
            rightMin = rightMin -> left;
        }
        root -> data = rightMin -> data;
        root -> right = deleteNode(root -> right, rightMin -> data, cmp);
    }
    return root;

}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}