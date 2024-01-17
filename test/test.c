#include <stdio.h>
#include <stdlib.h>

// Definition of a TreeNode
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Function to create a new TreeNode
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a sample binary tree
struct TreeNode* createSampleTree() {
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    root->left->left->left = createNode(8);
    root->left->left->right = createNode(9);
    // Add more nodes as needed
    // root->left->left->right->left = createNode(10);

    return root;
}

// Function to perform an in-order traversal of the tree
void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

int nonleafSum(struct TreeNode* root);
int nonLeafCount(struct TreeNode *root);
int leafCount(struct TreeNode *root);
int leafSum(struct TreeNode *root);

int main() {
    struct TreeNode* root = createSampleTree();

    printf("Total sum of non-leaf node: %d \n", nonleafSum(root));
    printf("Total sum of leaf nodes: %d \n", leafSum(root));
    printf("Total number of non-leaf nodes: %d \n", nonLeafCount(root));
    printf("Total number of leaf nodes: %d \n", leafCount(root));
    // Free allocated memory
    // (In a real application, you would want to free the memory when done using the tree)
    return 0;
}

int nonleafSum(struct TreeNode* root) {
    if (root==NULL) {
        return 0;
    }

    if (root->left==NULL && root->right==NULL) {
        return 0;
    }
    int leftSum = nonleafSum(root->left);
    int rightSum = nonleafSum(root->right);
    return root->data + leftSum + rightSum;
}

int leafSum(struct TreeNode *root) {
    if (root==NULL) {
        return 0;
    }
    if (root->left==NULL && root->right==NULL) {
        return root->data;
    }
    int leftSum = leafSum(root->left);
    int rightSum = leafSum(root->right);
    return leftSum + rightSum;
}

int nonLeafCount(struct TreeNode *root) {
    if (root==NULL) {
        return 0;
    }
    if (root->right==NULL && root->left==NULL) {
        return 0;
    }
    else {
        int leftSum = nonLeafCount(root->left);
        int rightSum = nonLeafCount(root->right);
        return 1+leftSum+rightSum;
    } 
}

int leafCount (struct TreeNode *root) {
    if (root==NULL) {
        return 0;
    }
    if (root->left==NULL && root->right==NULL) {
        return 1;
    }
    else {
        int leftSum = leafCount(root->left);
        int rightSum = leafCount(root->right);
        return leftSum + rightSum;
    }
}