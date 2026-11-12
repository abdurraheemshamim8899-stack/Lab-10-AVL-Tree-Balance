
#include <iostream>
#include <algorithm>
using namespace std;

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

class AVLTree {
private:

    // Calculate height
    int height(Node* node) {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    // Calculate balance factor
    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;

        return height(node->left) -
            height(node->right);
    }

    // Right rotation (LL case)
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

    // Left rotation (RR case)
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

    // Recursive insertion
    Node* insertNode(Node* node, int value) {

        // Normal BST insertion
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insertNode(node->left, value);

        else if (value > node->data)
            node->right = insertNode(node->right, value);

        else {
            cout << "Duplicate value not allowed!\n";
            return node;
        }

        // Update height
        node->height = 1 + max(height(node->left),
            height(node->right));

        // Calculate balance factor
        int balance = getBalance(node);

        // LL Case
        if (balance > 1 &&
            value < node->left->data) {
            cout << "LL Rotation performed.\n";
            return rightRotate(node);
        }

        // RR Case
        if (balance < -1 &&
            value > node->right->data) {
            cout << "RR Rotation performed.\n";
            return leftRotate(node);
        }

        // LR Case
        if (balance > 1 &&
            value > node->left->data) {
            cout << "LR Rotation performed.\n";

            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 &&
            value < node->right->data) {
            cout << "RL Rotation performed.\n";

            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Inorder traversal
    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Preorder traversal
    void preorder(Node* node) {
        if (node == nullptr)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    // Postorder traversal
    void postorder(Node* node) {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    Node* root = nullptr;

public:

    void insert(int value) {
        root = insertNode(root, value);
    }

    void displayInorder() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }

        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }

    void displayPreorder() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }

        cout << "Preorder: ";
        preorder(root);
        cout << endl;
    }

    void displayPostorder() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }

        cout << "Postorder: ";
        postorder(root);
        cout << endl;
    }
};

int main1() {

    AVLTree tree;
    int choice, value;

    do {
        cout << "\n===== AVL TREE MENU =====\n";
        cout << "1. Insert Node\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Postorder Traversal\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter value: ";
            cin >> value;
            tree.insert(value);
            break;

        case 2:
            tree.displayInorder();
            break;

        case 3:
            tree.displayPreorder();
            break;

        case 4:
            tree.displayPostorder();
            break;

        case 5:
            cout << "Program terminated.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
