#include <iostream>

/*
*Name: B-Tree insert
*Author: Wesley Hixon
*Date Last Updated: 12/4/2025
*Purpose: Demonstrate a B-Tree insert function
*/

template <size_t t>
struct nodeType{
    int maxKeys = 2t - 1;
    int maxChildren = 2t;

    int numChildren;
    int numKeys;
    int keys[maxKeys];
    bool leaf;
    nodeType<t> *children[maxChildren] = nullptr;

    void splitChild()
};

template <size_t t>
class bTree{
    private:
        nodeType<t>* root = nullptr;
        void insert(nodeType<t>* node = root, int key){
            for(int i = 0; i < node->numKeys; i++){

            }
        }
};

int main(){

    return 0;
}