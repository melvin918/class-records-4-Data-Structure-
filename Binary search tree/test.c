#include "BST.h"
#include <stdio.h>

void Inorder(Node *root) {
    if(!root) return;
    Inorder(root -> left);
    printf("%d ", *(int*)(root -> data));                     
    Inorder(root -> right);
}  

int cmp (const void *a, const void *b) {
    int x = *(int*) a;
    int y = *(int*) b;
    if (x == y) return 0;
    if (x > y) return 1;
    return -1;
}

int main() {
    Node *root = NULL;
    int a = 0;
    int b = 1;
    int c = 2;

    root = insertNode(root, &a, cmp);
    root = insertNode(root, &b, cmp);
    root = insertNode(root, &c, cmp);
    Inorder(root);
    printf("\n");

    root = deleteNode(root, &a, cmp);
    Inorder(root);
    printf("\n");

    root = deleteNode(root, &a, cmp);
    Inorder(root);
    root = deleteNode(root, &b, cmp);
    root = deleteNode(root, &c, cmp);
    Inorder(root);

    return 0;
}