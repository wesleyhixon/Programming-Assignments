#include <iostream>
#include <vector>

/*
*Name: B-Tree insert
*Author: Wesley Hixon
*Date Last Updated: 12/4/2025
*Purpose: Demonstrate a B-Tree insert function
*/

template <size_t t>
struct nodeType{
    static constexpr size_t maxKeys = 2 * t - 1;
    static constexpr size_t maxChildren = 2 * t;

    int numChildren = 0;
    int numKeys = 0;
    std::vector<int> keys;
    bool leaf;
    std::vector<nodeType<t>*> children;

    nodeType(){
        keys.resize(maxKeys);
        children.resize(maxChildren, nullptr);
        leaf = true;
    }
    void splitChild(int childIndex){
        nodeType<t>* leftChild = children[childIndex];
        nodeType<t>* newRight = new nodeType<t>;
        newRight->leaf = leftChild->leaf;

        leftChild->numKeys = t - 1;
        newRight->numKeys = t - 1;

        for(int i = 0; i < t - 1; i++){
            newRight->keys[i] = leftChild->keys[i + t];
        }
        if(leftChild->leaf == false){
            for(int i = 0; i < t; i++){
                newRight->children[i] = leftChild->children[i+t];
            }
            leftChild->numChildren = t;
            newRight->numChildren = t;
        }

        
        for(int i = numChildren - 1; i > childIndex; i--){
            children[i + 1] = children[i];
        }

        children[childIndex + 1] = newRight;

        int keyIndex = childIndex;

        for(int i = numKeys - 1; i > keyIndex; i--){
            keys[i] = keys[i - 1];
        }

        keys[keyIndex] = leftChild->keys[t - 1];

        numChildren++;
        numKeys++;
    }

    void insertNonFull(int key){
        
        int insertionIndex = numKeys;

        for(int i = 0; i < numKeys; i++){
            if(keys[i] > key){
                insertionIndex = i;
                break;
            }
        }

        if(leaf){
            for(int i = numKeys - 1; i > insertionIndex; i--){
                keys[i] = keys[i - 1];
            }
            keys[insertionIndex] = key;
            numKeys++;
        }
        else{
            int childIndex = insertionIndex;
            if(children[childIndex]->numKeys == children[childIndex]->maxKeys){
                splitChild(childIndex);
            }

            if(keys[childIndex] > key) childIndex++;
            children[childIndex]->insertNonFull(key);
        }
    }
};

template <size_t t>
class bTree{
    private:
        static constexpr int maxKeys = 2* t - 1;
        static constexpr int maxChildren = 2* t;

        nodeType<t>* root = nullptr;

    public:
        void insert(int key){
            if(root == nullptr){
                root = new nodeType<t>();
                root->leaf = true;
                root->insertNonFull(key);
                return;
            }

            if(root->numKeys == root->maxKeys){
                nodeType<t>* newRoot = new nodeType<t>();
                newRoot->leaf = false;
                newRoot->children[0] = root;
                newRoot->numChildren++;

                newRoot->splitChild(0);


                int i = 0;
                if(newRoot->keys[0] < key) i++;
                newRoot->children[i]->insertNonFull(key);

                root = newRoot;
            }

            int insertionIndex = maxKeys;

            
            if(root->leaf){
                root->insertNonFull(key);
            }
            else if(root->children[insertionIndex]->numKeys == maxKeys){
                root->splitChild(insertionIndex);
                root->insertNonFull(key);
            }
        }
        void traverse(){
            int i;
            for (i = 0; i < root->numKeys; ++i) {
                if (!root->leaf)
                    traverse(root->children[i]);
                std::cout << root->keys[i] << " ";
            }
            if (!root->leaf)
                traverse(root->children[i]);
        }
        void traverse(nodeType<t>* node) {
            int i;
            for (i = 0; i < node->numKeys; ++i) {
                if (!node->leaf)
                    traverse(node->children[i]);
                std::cout << node->keys[i] << " ";
            }
            if (!node->leaf)
                traverse(node->children[i]);
        }
};

int main(){
    bTree<2> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    tree.traverse();
    return 0;
}