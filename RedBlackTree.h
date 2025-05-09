#pragma once
#include <iostream>
#include <iomanip> 
#include <string> 
#include <sstream>
#include "AnimationSteps.h"
enum Color { RED, BLACK };
using namespace std;


template <typename DataType>
class RedBlackTree
{
private:
    class Node {
    public:
        DataType data;
        Node* leftChild;
        Node* rightChild;
        Node* parent;
        Color color;
        Node(DataType item)
            : data(item), leftChild(nullptr), rightChild(nullptr), parent(nullptr), color(RED) {
        }
        Node* getRoot() const { return root; }
    };
    Node* root;

    void rotateLeft(Node*& node, AnimationSteps& steps);
    void rotateRight(Node*& node, AnimationSteps& steps);
    void balanceInsert(Node*& node, AnimationSteps& steps);
    void balanceDelete(Node*& node, AnimationSteps& steps);
    Node* findMinimum(Node* node);
    void deleteNode(Node*& node, AnimationSteps& steps);
  /*  void inorderTraversal(Node* node);*/ //we don't need it in gui 
    void transplant(Node* u, Node* v);
    void displayTree(Node* root, string indent, bool last);


public:

    RedBlackTree();

    void insert(DataType data, AnimationSteps& steps);
    void remove(DataType data, AnimationSteps& steps);
    void display();
    Node* getRoot();
    bool search(DataType key);
    int getNodeData(Node* node) { return node ? node->data : -1; }
    typename RedBlackTree<DataType>::Node* searchTreeHelper(Node* node, DataType key);
};


// Constructor definition for RedBlackTree

template<typename DataType>
void RedBlackTree<DataType>::rotateLeft(Node*& node, AnimationSteps& steps)
{
    steps.AddStep("RotateLeft", node->data);
    Node* rightChild = node->rightChild;
    node->rightChild = rightChild->leftChild;

    if (rightChild->leftChild != nullptr)
        rightChild->leftChild->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    }
    else if (node == node->parent->leftChild) {
        node->parent->leftChild = rightChild;
    }
    else {
        node->parent->rightChild = rightChild;
    }

    rightChild->leftChild = node;
    node->parent = rightChild;
}

template<typename DataType>
void RedBlackTree<DataType>::rotateRight(Node*& node, AnimationSteps& steps)
{
    steps.AddStep("RotateRight", node->data);
    Node* leftChild = node->leftChild;
    node->leftChild = leftChild->rightChild;

    if (leftChild->rightChild != nullptr)
        leftChild->rightChild->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    }
    else if (node == node->parent->rightChild) {
        node->parent->rightChild = leftChild;
    }
    else {
        node->parent->leftChild = leftChild;
    }

    leftChild->rightChild = node;
    node->parent = leftChild;
}

template<typename DataType>
void RedBlackTree<DataType>::balanceInsert(Node*& node, AnimationSteps& steps) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;

    while (node != root && node->color == RED && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->leftChild) {
            Node* uncle = grandparent->rightChild;
            // case 1:uncle is red
            if (uncle != nullptr && uncle->color == RED) {
                
                steps.AddStep("Recolor", grandparent->data);
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent; // Move up 
            }
            
            else {
                // case 2:uncle is black or nil
                if (node == parent->rightChild) {
                    rotateLeft(parent,steps); 
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent,steps);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        else {
            Node* uncle = grandparent->leftChild;
            if (uncle != nullptr && uncle->color == RED) {
                steps.AddStep("Recolor", grandparent->data);
                // Case 1: Uncle is red
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent; // Move up the tree
            }
            else {
                // Case 2: Uncle is black
                if (node == parent->leftChild) {
                    rotateRight(parent,steps);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent,steps);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    // Ensure the root is always black
    root->color = BLACK;
  
}
template<typename DataType>
void RedBlackTree<DataType>::balanceDelete(Node*& node, AnimationSteps& steps)
{
    while (node != nullptr && node != root && (node->color == BLACK)) {
        if (node->parent != nullptr) {
            if (node == node->parent->leftChild) {
                Node* sibling = node->parent->rightChild;
                if (sibling != nullptr && sibling->color == RED) {
                    steps.AddStep("RecolorSibling", sibling->data);
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateLeft(node->parent,steps);
                    sibling = node->parent->rightChild;
                }

                if ((sibling == nullptr || sibling->leftChild == nullptr || sibling->leftChild->color == BLACK) &&
                    (sibling == nullptr || sibling->rightChild == nullptr || sibling->rightChild->color == BLACK)) {
                    if (sibling != nullptr) {
                        steps.AddStep("RecolorSibling", sibling->data);
                        sibling->color = RED;
                    }
                    node = node->parent;
                }
                else {
                    if (sibling != nullptr && (sibling->rightChild == nullptr || sibling->rightChild->color == BLACK)) {
                        steps.AddStep("RecolorSibling", sibling->data);
                        if (sibling->leftChild != nullptr)
                            sibling->leftChild->color = BLACK;

                        sibling->color = RED;
                        rotateRight(sibling,steps);
                        sibling = node->parent->rightChild;
                    }

                    if (sibling != nullptr) {
                        sibling->color = node->parent->color;
                        node->parent->color = BLACK;

                        if (sibling->rightChild != nullptr)
                            sibling->rightChild->color = BLACK;

                        rotateLeft(node->parent,steps);
                        node = root;
                    }
                }
            }
            else {
                Node* sibling = node->parent->leftChild;

                if (sibling != nullptr && sibling->color == RED) {
                    steps.AddStep("RecolorSibling", sibling->data);
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateRight(node->parent,steps);
                    sibling = node->parent->leftChild;
                }

                if ((sibling == nullptr || sibling->leftChild == nullptr || sibling->leftChild->color == BLACK) &&
                    (sibling == nullptr || sibling->rightChild == nullptr || sibling->rightChild->color == BLACK)) {
                    if (sibling != nullptr) {
                        steps.AddStep("RecolorSibling", sibling->data);
                        sibling->color = RED;
                    }
                    node = node->parent;
                }
                else {
                    if (sibling != nullptr && (sibling->leftChild == nullptr || sibling->leftChild->color == BLACK)) {
                        if (sibling->rightChild != nullptr)
                            sibling->rightChild->color = BLACK;
                        steps.AddStep("RecolorSibling", sibling->data);
                        sibling->color = RED;
                        rotateLeft(sibling,steps);
                        sibling = node->parent->leftChild;
                    }

                    if (sibling != nullptr) {
                        sibling->color = node->parent->color;
                        node->parent->color = BLACK;

                        if (sibling->leftChild != nullptr)
                            sibling->leftChild->color = BLACK;

                        rotateRight(node->parent,steps);
                        node = root;
                    }
                }
            }
        }
        else {
            break;
        }
    }

    if (node != nullptr)
        node->color = BLACK;
}

template<typename DataType>
typename RedBlackTree<DataType>::Node* RedBlackTree<DataType>::findMinimum(Node* node)
{
    while (node != nullptr && node->leftChild != nullptr)
        node = node->leftChild;
    return node;
}

template<typename DataType>
void RedBlackTree<DataType>::deleteNode(Node*& node, AnimationSteps& steps)
{
    Node* z = root;
    Node* y;
    Node* x;

    while (z != nullptr && z->data != node->data) {
        if (node->data < z->data)
            z = z->leftChild;
        else
            z = z->rightChild;
    }

    if (z == nullptr) return;

    y = z;
    Color originalColor = y->color;

    if (z->leftChild == nullptr) {
        x = z->rightChild;
        transplant(z, z->rightChild);
    }
    else if (z->rightChild == nullptr) {
        x = z->leftChild;
        transplant(z, z->leftChild);
    }
    else {
        y = findMinimum(z->rightChild);
        originalColor = y->color;
        x = y->rightChild;

        if (y->parent == z) {
            if (x != nullptr)
                x->parent = y;
        }
        else {
            transplant(y, y->rightChild);
            y->rightChild = z->rightChild;
            y->rightChild->parent = y;
        }

        transplant(z, y);
        y->leftChild = z->leftChild;
        y->leftChild->parent = y;
        y->color = z->color;
    }

    if (originalColor == BLACK)
        balanceDelete(x,steps);
}
template<typename DataType>
typename RedBlackTree<DataType>::Node* RedBlackTree<DataType>::searchTreeHelper(Node* node, DataType key) {
    if (node == NULL || key == node->data) {
        return node;
    }
    if (key < node->data) {
        return searchTreeHelper(node->leftChild, key);
    }
    return searchTreeHelper(node->rightChild, key);
}
//don't need it in gui
//template<typename DataType>
//void RedBlackTree<DataType>::inorderTraversal(Node* node)
//{
//    if (node == nullptr)
//        return;
//
//    inorderTraversal(node->leftChild);
//    cout << node->data << " ";
//    inorderTraversal(node->rightChild);
//}

template<typename DataType>
void RedBlackTree<DataType>::transplant(Node* u, Node* v)
{
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->leftChild) {
        u->parent->leftChild = v;
    }
    else {
        u->parent->rightChild = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

template<typename DataType>
void RedBlackTree<DataType>::displayTree(Node* root, string indent, bool last)
{

    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";  // Right child
            indent += "   ";
        }
        else {
            cout << "L----";  // Left child
            indent += "|  ";
        }

        string sColor = root->color == RED ? "RED" : "BLACK";
        cout << root->data << "(" << sColor << ")" << endl;

        displayTree(root->leftChild, indent, false);
        displayTree(root->rightChild, indent, true);
    }
}

template<typename DataType>
inline RedBlackTree<DataType>::RedBlackTree() :root(nullptr)
{
}

template<typename DataType>
void RedBlackTree<DataType>::insert(DataType data, AnimationSteps& steps)
{ // Step 1: Handle duplication
    steps.AddStep("Insert", data);
    Node* temp = root;
    while (temp != nullptr) {
        if (data == temp->data) {

            return; // Duplicate found, do not insert
        }
        else if (data < temp->data) {
            temp = temp->leftChild;
        }
        else {
            temp = temp->rightChild;
        }
    }

    // Step 2: Insert the new node
    Node* newNode = new Node(data);
    if (root == nullptr) {
        root = newNode;
        root->color = BLACK;
        return;
    }

    temp = root;
    Node* parent = nullptr;

    while (temp != nullptr) {
        parent = temp;
        if (data < temp->data)
            temp = temp->leftChild;
        else
            temp = temp->rightChild;
    }

    newNode->parent = parent;

    if (data < parent->data)
        parent->leftChild = newNode;
    else
        parent->rightChild = newNode;

    // Step 3: Balance the tree after insertion
    balanceInsert(newNode,steps);
}

template<typename DataType>
void RedBlackTree<DataType>::remove(DataType data, AnimationSteps& steps)
{
    steps.AddStep("Remove", data);
    Node* node = new Node(data);
    deleteNode(node,steps);
    delete node;
}

template<typename DataType>
void RedBlackTree<DataType>::display()
{
    //don't need it in gui
    //cout << "Inorder Traversal: ";
    //inorderTraversal(root); // Call inorder traversal to display elements
    //cout << endl;

    cout << "Tree Structure:" << endl;
    if (root) {
        displayTree(this->root, "", true); // Display the tree structure
    }
}

template<typename DataType>
typename RedBlackTree<DataType>::Node* RedBlackTree<DataType>::getRoot()
{
    return root;
}

template<typename DataType>
inline bool RedBlackTree<DataType>::search(DataType key)
{
    Node* result = searchTreeHelper(root, key);
    if (result == nullptr) {
        return false; // Key doesn't exist
    }
    return true; // Key exists
}

