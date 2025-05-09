// RedBlackTreeWrapper.h
#pragma once
#include "RedBlackTree.h"
#include "AnimationSteps.h"
#include <sstream> 
using namespace System;
using namespace std;

namespace RedBlackTreeWrapper {

    public ref class RedBlackTreeManaged {
    private:
        RedBlackTree<int>* tree; // Pointer to the native RedBlackTree
        AnimationSteps* animationSteps; // Animation steps manager
    public:
        
        RedBlackTreeManaged() {
            tree = new RedBlackTree<int>();
            animationSteps = new AnimationSteps();
        }

        ~RedBlackTreeManaged() {
            this->!RedBlackTreeManaged();
        }

        !RedBlackTreeManaged() {
            delete tree;
            delete animationSteps;
        }

        // Method to insert a value
        void Insert(int value) {
            animationSteps->Clear(); // Clear previous steps
            tree->insert(value, *animationSteps);
        }

        // Method to delete a value
        void Remove(int value) {
            animationSteps->Clear();
            tree->remove(value, *animationSteps); 
        }

        bool Search(int value) {
            return tree->search(value); // Call the unmanaged method
        }

        // Method to display the tree structure
        String^ Display() {
            ostringstream oss;
            streambuf* oldCoutBuffer = cout.rdbuf(oss.rdbuf()); // Redirect cout to string stream
            tree->display(); // Call the display method of the native tree
            cout.rdbuf(oldCoutBuffer); // Restore cout
            return gcnew String(oss.str().c_str());
        }

        // Method to get the root of the tree
        int GetRootData() {
            return tree->getNodeData(tree->getRoot());
        }

        // Retrieve animation steps as managed objects
        System::Collections::Generic::List<System::Tuple<System::String^, int>^>^ GetAnimationSteps() {
            auto steps = gcnew System::Collections::Generic::List<System::Tuple<System::String^, int>^>();
            for (const auto& step : animationSteps->GetSteps()) {
                steps->Add(gcnew System::Tuple<System::String^, int>(gcnew System::String(step.first.c_str()), step.second));
            }
            return steps;

        }
        int GetLeftChild(int nodeData) {
            auto node = tree->searchTreeHelper(tree->getRoot(), nodeData);
            return node && node->leftChild ? tree->getNodeData(node->leftChild) : -1;
        }

        int GetRightChild(int nodeData) {
            auto node = tree->searchTreeHelper(tree->getRoot(), nodeData);
            return node && node->rightChild ? tree->getNodeData(node->rightChild) : -1;
        }
        bool IsNodeRed(int nodeData) {
            auto node = tree->searchTreeHelper(tree->getRoot(), nodeData);
            return node && node->color == RED;
        }


    };
}