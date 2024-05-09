#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cctype>
using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

Node* buildExpressionTree(ifstream& inputFile) {
    string expression;
    getline(inputFile, expression);

    stack<Node*> nodes;

    for (char c : expression) {
        if (isspace(c)) {
            continue;
        }
        else if (isOperator(c)) {
            if (nodes.size() < 2) {
                cerr << "Invalid expression: insufficient operands for operator" << endl;
                return nullptr;
            }

            Node* newNode = new Node{ string(1, c), nullptr, nullptr };
            newNode->right = nodes.top();
            nodes.pop();
            newNode->left = nodes.top();
            nodes.pop();
            nodes.push(newNode);
        }
        else if (isdigit(c)) {
            nodes.push(new Node{ string(1, c), nullptr, nullptr });
        }
        else {
            cerr << "Invalid character in expression: " << c << endl;
            return nullptr;
        }
    }

    if (nodes.size() != 1) {
        cerr << "Invalid expression: too many operands or operators" << endl;
        return nullptr;
    }

    return nodes.top();
}

void printTree(Node* root) {
    if (root != nullptr) {
        printTree(root->left);
        cout << root->value << " ";
        printTree(root->right);
    }
}

void deleteTree(Node* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

Node* insertNode(Node* root, string value) {
    if (root == nullptr) {
        root = new Node{ value, nullptr, nullptr };
    }
    else if (value < root->value) {
        root->left = insertNode(root->left, value);
    }
    else {
        root->right = insertNode(root->right, value);
    }
    return root;
}

Node* findMinimum(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* deleteNode(Node* root, string value) {
    if (root == nullptr) {
        return root;
    }
    else if (value < root->value) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMinimum(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

Node* search(Node* root, string value) {
    if (root == nullptr || root->value == value) {
        return root;
    }
    if (value < root->value) {
        return search(root->left, value);
    }
    return search(root->right, value);
}

int main() {
    ifstream inputFile("input1.txt");
    if (!inputFile.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    Node* root = buildExpressionTree(inputFile);
    inputFile.close();

    if (root != nullptr) {
        cout << "Expression tree built successfully:" << endl;
        printTree(root);
        cout << endl;

        string valueToAdd = "8";
        root = insertNode(root, valueToAdd);
        cout << "After adding " << valueToAdd << ":" << endl;
        printTree(root);
        cout << endl;

        string valueToDelete = "+";
        root = deleteNode(root, valueToDelete);
        cout << "After deleting " << valueToDelete << ":" << endl;
        printTree(root);
        cout << endl;

        string valueToSearch = "3";
        Node* foundNode = search(root, valueToSearch);
        if (foundNode != nullptr) {
            cout << "Node with value " << valueToSearch << " found" << endl;
        }
        else {
            cout << "Node with value " << valueToSearch << " not found" << endl;
        }

        deleteTree(root);
    }

    return 0;
}
