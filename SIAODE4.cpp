﻿#include "BINWORK.h"



struct Node {
    int key;
    int row;
    Node* parent;
    Node* left;
    Node* right;
    int color;
};



class RedBlackTree {
private:
    Node* root;
    Node* TNULL;

    void initializeNULLNode(Node* node, Node* parent) {
        node->key = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }


    Node* searchTreeHelper(Node* node, int key) {
        if (node == TNULL || key == node->key) {
            return node;
        }

        if (key < node->key) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // For balancing the tree after deletion
    void deleteFix(Node* x) {
        Node* s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                }
                else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->left) {
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node* node, int key) {
        Node* z = TNULL;
        Node* x, *y;
        while (node != TNULL) {
            if (node->key == key) {
                z = node;
            }

            if (node->key <= key) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            deleteFix(x);
        }
    }

    // For balancing the tree after insertion
    void insertFix(Node* k) {
        Node* u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void printHelper(Node* root, string indent, bool last) {
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->key << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

   
    Node* searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }

    Node* minimum(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    Node* maximum(Node* node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    Node* successor(Node* x) {
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        Node* y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node* predecessor(Node* x) {
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        Node* y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(int key,int row) {
        Node* node = new Node;
        node->parent = nullptr;
        node->key = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;
        node->row = row;

        Node* y = nullptr;
        Node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        }
        else if (node->key < y->key) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        insertFix(node);
    }

    Node* getRoot() {
        return this->root;
    }

    void deleteNode(int key) {
        deleteNodeHelper(this->root, key);
    }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }
};


int main() {
    RedBlackTree bst;
    cout << "1 Get\n2 Delete\n3 Print Tree\n4 Print full bin file\n-1 End\n";
    int input;
    string name;
    //Имя бинарного файла в котором хранится вся информация
    string binName = "data";
    //Poggers.txt файл с исходными записями, можно изменить название
    CreateBinFile("Poggers.txt", binName);
    vector<record> R = outBinFile(binName);
    for (int i = 0; i < R.size(); ++i) {
        bst.insert(R[i].key, i);
    }
    cin >> input;
    while (input != -1) {
        switch (input)
        {
        case 1:
            cout << "Print key:";
            cin >> input;
            if (bst.searchTree(input)->key != 0) {
                record r = readRecordFromBin(binName, bst.searchTree(input)->row);
                cout << r.key << ' ' << r.data << '\n';
            }
            else {
                cout << "Not Found\n";
            }
            break;
        case 2:
            cout << "Print key:";
            cin >> input;
            if (bst.searchTree(input)->key != 0) {
                int row = bst.searchTree(input)->row;
                bst.deleteNode(input);
                deleteRecord(binName, row);
            }
        case 3:
            bst.printTree();
            break;
        case 4:
            R = outBinFile(binName);
            for (int i = 0; i < R.size(); ++i) {
                cout << R[i].key << ' ' << R[i].data << '\n';
            }
            break;
        default:
            cout << "Wrong input\n";
            break;
        }
        cin >> input;
    }
}

