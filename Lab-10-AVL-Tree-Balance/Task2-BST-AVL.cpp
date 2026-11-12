
#include <iostream>
#include <algorithm>
using namespace std;

// Node class
class Node {
public:
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

// Normal BST
class BST {
private:
    Node* root;

    Node* insertNode(Node* node, int value) {

        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insertNode(node->left, value);

        else if (value > node->data)
            node->right = insertNode(node->right, value);

        return node;
    }

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;

        return 1 + max(getHeight(node->left),
            getHeight(node->right));
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void display() {
        inorder(root);
    }

    int treeHeight() {
        return getHeight(root);
    }
};

// AVL Tree
class AVL {
private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    int balance(Node* node) {
        if (node == nullptr)
            return 0;

        return height(node->left) -
            height(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left),
            height(y->right));

        x->height = 1 + max(height(x->left),
            height(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left),
            height(x->right));

        y->height = 1 + max(height(y->left),
            height(y->right));

        return y;
    }

    Node* insertNode(Node* node, int value) {

        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insertNode(node->left, value);

        else if (value > node->data)
            node->right = insertNode(node->right, value);

        else
            return node;

        node->height = 1 + max(height(node->left),
            height(node->right));

        int bf = balance(node);

        // LL
        if (bf > 1 && value < node->left->data)
            return rightRotate(node);

        // RR
        if (bf < -1 && value > node->right->data)
            return leftRotate(node);

        // LR
        if (bf > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (bf < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;

        return 1 + max(getHeight(node->left),
            getHeight(node->right));
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

public:
    AVL() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void display() {
        inorder(root);
    }

    void displayStructure() {
        preorder(root);
    }

    int treeHeight() {
        return getHeight(root);
    }
};

int main2() {

    BST normalTree;
    AVL avlTree;

    int values[] = { 10, 20, 30, 40, 50, 60, 70 };

    // Insert values into both trees
    for (int i = 0; i < 7; i++) {
        normalTree.insert(values[i]);
        avlTree.insert(values[i]);
    }

    cout << "\n===== NORMAL BST =====\n";

    cout << "Inorder: ";
    normalTree.display();

    cout << "\nHeight: ";
    cout << normalTree.treeHeight();

    cout << "\n\n===== AVL TREE =====\n";

    cout << "Inorder: ";
    avlTree.display();

    cout << "\nPreorder: ";
    avlTree.displayStructure();

    cout << "\nHeight: ";
    cout << avlTree.treeHeight();

    cout << "\n";

    return 0;
}
