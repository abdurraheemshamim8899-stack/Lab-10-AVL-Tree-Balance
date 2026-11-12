
#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int alertID;
    int height;

    Node* left;
    Node* right;

    Node(int id) {
        alertID = id;
        height = 1;

        left = nullptr;
        right = nullptr;
    }
};

class AVLTree {
private:
    Node* root;

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

    // Right rotation
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

    // Left rotation
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

    // Insert Alert ID
    Node* insertNode(Node* node, int id) {

        if (node == nullptr)
            return new Node(id);

        if (id < node->alertID)
            node->left = insertNode(node->left, id);

        else if (id > node->alertID)
            node->right = insertNode(node->right, id);

        else {
            cout << "Duplicate Alert ID not allowed!\n";
            return node;
        }

        // Update height
        node->height = 1 + max(height(node->left),
            height(node->right));

        // Calculate balance
        int bf = getBalance(node);

        // LL
        if (bf > 1 && id < node->left->alertID)
            return rightRotate(node);

        // RR
        if (bf < -1 && id > node->right->alertID)
            return leftRotate(node);

        // LR
        if (bf > 1 && id > node->left->alertID) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (bf < -1 && id < node->right->alertID) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Search Alert ID
    bool searchNode(Node* node, int id) {

        if (node == nullptr)
            return false;

        if (node->alertID == id)
            return true;

        if (id < node->alertID)
            return searchNode(node->left, id);

        return searchNode(node->right, id);
    }

    // Display IDs in ascending order
    void inorder(Node* node) {

        if (node == nullptr)
            return;

        inorder(node->left);

        cout << node->alertID << " ";

        inorder(node->right);
    }

public:

    AVLTree() {
        root = nullptr;
    }

    void insert(int id) {
        root = insertNode(root, id);
    }

    void search(int id) {
        if (searchNode(root, id))
            cout << "Alert ID " << id << " found!\n";
        else
            cout << "Alert ID " << id << " not found!\n";
    }

    void display() {
        cout << "Alert IDs in ascending order: ";
        inorder(root);
        cout << endl;
    }

    void displayRootBalance() {
        if (root == nullptr) {
            cout << "Tree is empty!\n";
            return;
        }

        cout << "Root Alert ID: " << root->alertID << endl;

        cout << "Root Balance Factor: "
            << getBalance(root) << endl;
    }
};

int main() {

    AVLTree tree;

    int values[] = { 40, 20, 60, 10, 30, 50, 70, 5 };

    // Insert test data
    cout << "Inserting Alert IDs...\n";

    for (int i = 0; i < 8; i++) {
        tree.insert(values[i]);
    }

    int choice, id;

    do {

        cout << "\n===== CYBERSECURITY ALERT SYSTEM =====\n";

        cout << "1. Insert Alert ID\n";
        cout << "2. Search Alert ID\n";
        cout << "3. Display Alert IDs\n";
        cout << "4. Display Root Balance Factor\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter Alert ID: ";
            cin >> id;

            tree.insert(id);
            break;

        case 2:
            cout << "Enter Alert ID to search: ";
            cin >> id;

            tree.search(id);
            break;

        case 3:
            tree.display();
            break;

        case 4:
            tree.displayRootBalance();
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
