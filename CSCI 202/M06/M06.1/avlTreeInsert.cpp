#include <iostream>

template <class Type>
struct nodeType{
    Type info;
    nodeType* leftLink;
    nodeType* rightLink;
};

class AVLTree{
    public:
        const AVLTree& operator=(const AVLTree& other){
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
            root = recursiveInsert(root, value);
        }

        nodeType<int>* recursiveInsert(nodeType<int>* node, int value) {
            if (!node) {
                node = new nodeType<int>{value, nullptr, nullptr};
                return node;
            }

            if (value < node->info)
                node->leftLink = recursiveInsert(node->leftLink, value);
            else if (value > node->info)
                node->rightLink = recursiveInsert(node->rightLink, value);
            else
                return node;

            int bf = balance(node);

            // LL
            if (bf > 1 && value < node->leftLink->info)
                return rightRotation(node);

            // RR
            if (bf < -1 && value > node->rightLink->info)
                return leftRotation(node);

            // LR
            if (bf > 1 && value > node->leftLink->info) {
                node->leftLink = leftRotation(node->leftLink);
                return rightRotation(node);
            }

            // RL
            if (bf < -1 && value < node->rightLink->info) {
                node->rightLink = rightRotation(node->rightLink);
                return leftRotation(node);
            }

            return node;
        }

        nodeType<int>* rightRotation(nodeType<int> *node){
            if(node == nullptr) return node;
            nodeType<int> *leftNode = node->leftLink;
            
            node->leftLink = leftNode->rightLink;
            leftNode->rightLink = node;

            return leftNode;
        }

        nodeType<int>* leftRotation(nodeType<int> *node){
            if(node == nullptr) return node;
            nodeType<int> *rightNode = node->rightLink;

            node->rightLink = rightNode->leftLink;
            rightNode->leftLink = node;

            return rightNode;
        }

        nodeType<int>* rotateLR(nodeType<int> *node){
            node->leftLink = leftRotation(node->leftLink);
            return rightRotation(node);

        }

        nodeType<int>* rotateRL(nodeType<int> *node){
            node->rightLink = rightRotation(node->rightLink);
            return leftRotation(node);
        }
        int balance(nodeType<int> *node){
            if(node == nullptr) return 0;

            return (height(node->leftLink) - height(node->rightLink));
        }
        int balance(){
            return balance(root);
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
        AVLTree(const AVLTree &other){
            copyTree(root, other.root);
        }
        AVLTree(){
            root = nullptr;
        }
        ~AVLTree(){
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
    AVLTree tree1, tree2;

    std::cout << "Tree insertions: " << std::endl;
    for(int i = 0; i < 10; i += 1){
        int randInt = rand() % 50;

        std::cout << randInt << ' ';
        tree1.insert(i);
    }

    std::cout << std::endl << "Balance: " << tree1.balance() << std::endl;

    std::cout << std::endl;
    return 0;
}