#include "Hash.h"
#include <string>
using namespace std;

// TODO: implement the hash function (remember to namespace to Hash::)
unsigned int Hash::PRH24(std::string s) {
    unsigned int p = 137;
    unsigned int p1 = 1;
    unsigned int m = 16777215;
    unsigned int hash = 0;
    for (auto i = s.begin(); i != s.end(); ++i) {
        hash = (hash + ((int(*i))*p1)) % m;
        p1 = (p1*p) % m;
    }
    return hash;
}