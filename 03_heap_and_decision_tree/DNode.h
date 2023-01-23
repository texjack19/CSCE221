#pragma once

#include "DecisionLogic.h"
using namespace std;

class DNode {
public:
    Decision key;
    int depth;
    DNode* parent;
    DNode* left;
    DNode* right;

DNode():key(), depth(0), parent(nullptr), left(nullptr), right(nullptr) {}
DNode(Decision k, int d, DNode* p, DNode* l, DNode* r):key(k), depth(d), parent(p), left(l), right(r) {}
};
