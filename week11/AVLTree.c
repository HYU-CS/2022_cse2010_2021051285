#include <stdio.h>
#include <stdlib.h>

#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

struct AvlNode
{
    int data;
    struct AvlNode *left, *right;
    int height;
};
typedef struct AvlNode AvlNode;

int height(AvlNode *node)
{
    if(node == NULL)
    {
        return -1;
    }
    else
    {
        return node->height;
    }
}

AvlNode *rotateLL(AvlNode *parent)
{
    AvlNode *child = parent->left;

    parent->left = child->right;
    child->right = parent;

    parent->height = max(height(parent->left), height(parent->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

AvlNode *rotateRR(AvlNode *parent)
{
    AvlNode *child = parent->right;

    parent->right = child->left;
    child->left = parent;

    parent->height = max(height(parent->left), height(parent->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

AvlNode *rotateLR(AvlNode *parent)
{
    parent->left = rotateRR(parent->left);
    return rotateLL(parent);
}

AvlNode *rotateRL(AvlNode *parent)
{
    parent->right = rotateLL(parent->right);
    return rotateRR(parent);
}

AvlNode *avlAdd(AvlNode *root, int data)
{
    if(root == NULL)
    {
        root = (AvlNode *)malloc(sizeof(AvlNode));
        if(root == NULL)
        {
            exit(EXIT_FAILURE);
        }

        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->height = 0;
    }
    else if(data < root->data)
    {
        root->left = avlAdd(root->left, data);

        if(height(root->left) - height(root->right) == 2)
        {
            if(data < root->left->data)
            {
                root = rotateLL(root);
            }
            else
            {
                root = rotateLR(root);
            }
        }
    }
    else if(data > root->data)
    {
        root->right = avlAdd(root->right, data);

        if(height(root->right) - height(root->left) == 2)
        {
            if(data < root->right->data)
            {
                root = rotateRL(root);
            }
            else
            {
                root = rotateRR(root);
            }
        }
    }
    else
    {
        printf("중복 키 삽입 오류\n");
        exit(EXIT_FAILURE);
    }

    root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}

AvlNode *avlSearch(AvlNode *node, int key)
{
    if(node == NULL)
    {
        return NULL;
    }

    if(key == node->data)
    {
        return node;
    }
    else if(key < node->data)
    {
        return avlSearch(node->left, key);
    }
    else
    {
        return avlSearch(node->right, key);
    }
}

void inorderTraveling(AvlNode *root)
{
    if(root != NULL)
    {
        inorderTraveling(root->left);
        printf("[%d] ", root->data);
        inorderTraveling(root->right);
    }
}

int main()
{
    AvlNode *root = NULL;

    root = avlAdd(root, 7);
    root = avlAdd(root, 8);
    root = avlAdd(root, 9);
    root = avlAdd(root, 2);
    root = avlAdd(root, 1);
    root = avlAdd(root, 5);
    root = avlAdd(root, 3);
    root = avlAdd(root, 6);
    root = avlAdd(root, 4);

    printf("\n검색: %d\n", avlSearch(root, 4)->data);
    printf("\n");
    inorderTraveling(root);

    return 0;
}