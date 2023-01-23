#include "Block.h"
#include "Hash.h"
#include <iostream>
using namespace std;

string mine(Block* b) {
    int val = 48; // ascii for "0"
    string nonce = "";
    while(!b->sign_block(nonce)) { // loop until valid hash is generated
        if(val % 122 == 0) { // go back to 0 if val reaches z
            val = 48;
        }
        nonce = nonce + char(val);
        val++;
    }
    return nonce;
}

int main() {
    Block* prevBlock;
    Block* b;
    Block* toPrint;
    string line;
    getline(cin, line);
    if (line != "") { // make a new block from read in transaction  prevBlock block)
     prevBlock = new Block(line, nullptr);
     prevBlock->nonce = mine(prevBlock);
    }
    while (line != "") { // for every line after the prevBlock, make a new block with prev pointer
        b = new Block(line, prevBlock);
        b->nonce = mine(b);
        getline(cin, line);
        prevBlock = b;
    }
    toPrint = b; // last block
    while(toPrint != nullptr) { // print contents of all blocks in the list
        cout << *toPrint;
        toPrint = toPrint->get_prev();
    }

    while (b != nullptr) { // once list is all printed out, delete contents
        Block* curr = b;
        b = b->get_prev();
        delete curr;
    }
    return 0;
}