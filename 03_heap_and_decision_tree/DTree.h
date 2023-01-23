#pragma once

#include <stdio.h>
#include "DNode.h"
#include "MaxHeap.h"
#include "Queue.h"
#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class DTree {
public:
DNode* root = nullptr;
int maxDepth = 10;
double delta = 0.00005;

Decision getMaxInformationGain(vector<string>& attributes, vector< vector<double> >& data, vector<int>& outcomes, vector<int>& instances) {
    // iterates through attributes vector and calls getInformationGain for each attribute
    MaxHeap<Decision> decisions;
    for (int i = 0; i < attributes.size(); i++) {
        decisions.insert(getInformationGain(attributes[i], data[i], outcomes, instances));
    }
    return decisions.removeMax();
}

void trainRecursive(vector<string>& attributes, vector< vector<double> >& data, vector<int>& outcomes, DNode* parent, int depth) {
    if (depth == maxDepth) { // return if depth has reached 10
        return;
    }
    else {
        Decision leftDecision = getMaxInformationGain(attributes, data, outcomes, parent->key.instancesBelow);
        DNode* leftNode = new DNode(leftDecision, depth, parent, nullptr, nullptr);
        leftNode->depth = depth;

        parent->left = leftNode;
        leftNode->parent = parent;

        if (leftDecision.informationGain > delta) {
            trainRecursive(attributes, data, outcomes, leftNode, leftNode->depth+1);
        }

        Decision rightDecision = getMaxInformationGain(attributes, data, outcomes, parent->key.instancesAbove);
        DNode* rightNode = new DNode(rightDecision, depth, parent, nullptr, nullptr);
        rightNode->depth = depth;

        parent->right = rightNode;
        rightNode->parent = parent;

        if (rightDecision.informationGain > delta) {
            trainRecursive(attributes, data, outcomes, rightNode, rightNode->depth+1);
        }
    }
}

void train(vector<string>& attributes, vector< vector<double> >& data, vector<int>& outcomes, vector<int>& instances) {
    // takes the set of attributes, all data, and the list of outcomes so that it can build the DTree
    // should call getMaxInformationGain to get the decision that should be turned into the next node
    root = new DNode(getMaxInformationGain(attributes, data, outcomes, instances), maxDepth, nullptr, nullptr, nullptr);
    root->depth = 0;
    trainRecursive(attributes, data, outcomes, root, (root->depth)+1);
}

int classify(vector<string>& attributes, vector<double>& data) {
    DNode* curr = root;
    DNode* prev = nullptr;
    int outcome = -1;
    while (curr != nullptr) {
        prev = curr;
        string att = curr->key.attribute;
        for (int i = 0; i < attributes.size(); i++) {
            if (att == attributes[i]) {
                if (data[i] <= curr->key.threshold) {
                    outcome = curr->key.majorityBelow;
                    curr = curr->left;
                }
                else {
                    outcome = curr->key.majorityAbove;
                    curr = curr->right;
                }
                break;
                }
            }
        }
    return prev->key.majorityOutcome;         
}

string levelOrderTraversal() {
    // implement from lecture
    stringstream ss;
    // Queue<DNode*> q;
    std::queue<DNode*> q;
    q.push(root);
    while (!q.empty()) {
        DNode* u = q.front();
        q.pop();
        ss << string(u->depth,'\t') << u->key;
        if (u->left != nullptr) {
            q.push(u->left);
        }
        if (u->right != nullptr){
            q.push(u->right);
        }        
    }
    return ss.str();
}

void deleteTree(DNode*& n) { // helper function for destructor
    if (n == nullptr) {return;}
    deleteTree(n->left);
    deleteTree(n->right);
    delete n;
    n = nullptr;
}

~DTree() {
    // delete tree
    deleteTree(root);
}

};