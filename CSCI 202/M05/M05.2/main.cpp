#include <iostream>

/*
*Name: Binary Search Trees
*Author: Wesley Hixon
*Date Last Updated: 11/26/2025
*Purpose: Binary search tree class with a function to find number of leaves and nodes with single parents.
*/

template <class Type>
struct nodeType{
    Type info;
    nodeType* leftLink;
    nodeType* rightLink;
};

class binarySearchTree{
    public:
        const binarySearchTree& operator=(const binarySearchTree& other){
            if(this != &other){
                destroy(root);
                root = nullptr;
                copyTree(root, other.root);
            }
            return *this;
        }
        bool isEmpty() const{
            if(!root) return true;
            else return false;
        }

        void preOrderTraversal(){
            preorder(root);
        }
        void inOrderTraversal(){
            inorder(root);
        }
        void postOrderTraversal(){
            postorder(root);
        }

        void destroyTree(){
            destroy(root);
        }
        int treeHeight() const{
            return height(root);
        }
        bool searchTree(const int &value){
            if(search(value)) return true;
            else return false;
        }
        void insert(const int &value){
            if(!root){
                root = new nodeType<int>;
                root->info = value;
                root->leftLink = nullptr;
                root->rightLink = nullptr;
                return;
            }

            nodeType<int>* current = root;
            nodeType<int>* trailCurrent;
            
            while(current != nullptr){
                trailCurrent = current;

                if(current->info == value){
                    std::cout << "Error: cannot insert duplicate value" << std::endl;
                    return;
                }
                if(current->info > value){
                    current = current->leftLink;
                }
                else{
                    current = current->rightLink;
                }
            }

            nodeType<int>* newNode = new nodeType<int>;
            newNode->info = value;
            newNode->leftLink = nullptr;
            newNode->rightLink = nullptr;

            if(trailCurrent->info > value){
                trailCurrent->leftLink = newNode;
            }
            else{
                trailCurrent->rightLink = newNode;
            }
        }

        void deleteByValue(int &value){
            nodeType<int>* p = search(value);

            deleteNode(p);
        }

        int treeLeavesCount(){
            return leavesCount(root);
        }
        int treeSingleParent(){
            return singleParent(root);
        }
        binarySearchTree(const binarySearchTree &other){
            copyTree(root, other.root);
        }
        binarySearchTree(){
            root = nullptr;
        }
        ~binarySearchTree(){
            destroy(root);
        }
    private:
        nodeType<int>* root = nullptr;

        void copyTree(nodeType<int> *&copiedTreeRoot, nodeType<int>* otherTreeRoot){
            if(otherTreeRoot == nullptr){
                copiedTreeRoot = nullptr;
                return;
            }

            copiedTreeRoot = new nodeType<int>;
            copiedTreeRoot->info = otherTreeRoot->info;
            copyTree(copiedTreeRoot->leftLink, otherTreeRoot->leftLink);
            copyTree(copiedTreeRoot->rightLink, otherTreeRoot->rightLink);
        }

        // Need to fix this function
        void deleteNode(nodeType<int>* p){
            if(!p){
                std::cout << "Error: cannot delete nullptr" << std::endl;
                return;
            }

            nodeType<int>* temp;
            
            if(p->leftLink == nullptr && p->rightLink == nullptr){
                delete p;
            }

            else if(p->leftLink == nullptr){
                temp = p;
                p = temp->rightLink;
                temp->rightLink = nullptr;
                delete temp;
            }

            else if(p->rightLink == nullptr){
                temp = p;
                p = temp->leftLink;
                temp->rightLink = nullptr;
                delete temp;
            }

            else{
                nodeType<int> *current = p;
                nodeType<int> *trailCurrent = nullptr;

                while(current->rightLink != nullptr){
                    trailCurrent = current;
                    current = current->rightLink;
                }

                p->info = current->info;

                if(trailCurrent == nullptr){
                    p->leftLink = current->leftLink;
                }
                else{
                    trailCurrent->rightLink = current->leftLink;
                }
                delete current;
            }

        }
        void destroy(nodeType<int> *p){
            if(!p){
                return;
            }
            destroy(p->leftLink);
            destroy(p->rightLink);
            delete p;
            p = nullptr;
        }
        void preorder(nodeType<int> *p){
            if(p == nullptr) return;

            std::cout << p->info << ' ';
            preorder(p->leftLink);
            preorder(p->rightLink);
        }
        void inorder(nodeType<int> *p){
            if(!p) return;

            inorder(p->leftLink);
            std::cout << p->info << ' ';
            inorder(p->rightLink);
        }
        void postorder(nodeType<int> *p){
            if(!p) return;

            postorder(p->leftLink);
            postorder(p->rightLink);
            std::cout << p->info << ' ';
        }
        nodeType<int>* search(const int &value){
            nodeType<int>* current = root;
            while(current != nullptr){
                if(current->info == value){
                    return current;
                }
                if(current->info > value){
                    current = current->leftLink;
                }
                else{
                    current = current->rightLink;
                }
            }

            return nullptr;
        }
        int height(nodeType<int> *p) const{
            if(!p) return 0;
            return 1 + max(height(p->leftLink), height(p->rightLink));
        }
        int max(int x, int y) const{
            if(x >= y) return x;
            else return y;
        }
        int leavesCount(nodeType<int> *p){
            if(!p){
                return 0;
            }
            if(p->leftLink == nullptr && p->rightLink == nullptr){
                return 1;
            }

            if(p->leftLink == nullptr){
                return leavesCount(p->rightLink);
            }
            else if(p->rightLink == nullptr){
                return leavesCount(p->leftLink);
            }
            else{
                return leavesCount(p->leftLink) + leavesCount(p->rightLink);
            }
        }
        int singleParent(nodeType<int> *p){
            if(!p){
                return 0;
            }
            if(p->leftLink == nullptr && p->rightLink == nullptr){
                return 0;
            }
            else if(p->leftLink == nullptr){
                return 1 + singleParent(p->rightLink);
            }
            else if(p->rightLink == nullptr){
                return 1 + singleParent(p->leftLink);
            }
            else{
                return singleParent(p->leftLink) + singleParent(p->rightLink);
            }
        }
};

int main(){
    binarySearchTree tree1, tree2;

    std::cout << "First tree insertions: " << std::endl;
    for(int i = 0; i < 100; i += 10){
        std::cout << i << ' ';
        tree1.insert(i);
    }

    std::cout << std::endl;


    std::cout << std::endl << "Leaves count: " << tree1.treeLeavesCount() << std::endl;
    std::cout << std::endl << "Nodes with a single child: " << tree1.treeSingleParent() << std::endl;

    std::cout << std::endl << "Second tree insertions: " << std::endl;

    int tree2inserts[10] = {40, 20, 60, 10, 30, 50, 70, 0, 80, 90};

    for(int i : tree2inserts){
        std::cout << i << ' ';
        tree2.insert(i);
    }

    std::cout << std::endl << "Leaves count: " << tree2.treeLeavesCount() << std::endl;
    std::cout << std::endl << "Nodes with a single child: " << tree2.treeSingleParent() << std::endl;
    return 0;
}