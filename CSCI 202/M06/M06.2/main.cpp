#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

struct nodeType{
    int data;
    std::vector<nodeType*> neighbors;
};

class graphType{
    private:
        std::vector<nodeType*> nodes;

        void depthFirstRec(nodeType* A, std::unordered_set<nodeType*> &visited){
            if(!A || visited.count(A)) return;

            visited.insert(A);

            std::cout << A->data << ' ';

            for(nodeType* node : A->neighbors){
                depthFirstRec(node, visited);
            }
        }

    public:
        nodeType* insertNode(int value){
            nodeType* newNode = new nodeType;
            newNode->data = value;

            nodes.push_back(newNode);

            return newNode;
        }
        void link(nodeType* A, nodeType* B){
            if(std::find(A->neighbors.begin(), A->neighbors.end(), B) != A->neighbors.end()) return;

            A->neighbors.push_back(B);
            B->neighbors.push_back(A);
        }

        void depthFirst(nodeType* start){
            std::unordered_set<nodeType*> visited;
            depthFirstRec(start, visited);
        }

        void breadthFirst(nodeType* start){
            std::unordered_set<nodeType*> visited;
            std::queue<nodeType*> nodeQueue;

            nodeQueue.push(start);
            visited.insert(start);

            while(!nodeQueue.empty()){
                nodeType* node = nodeQueue.front();
                nodeQueue.pop();

                std::cout << node->data << ' ';

                for(nodeType* neighbor : node->neighbors){
                    if(!visited.count(neighbor)){
                        visited.insert(neighbor);
                        nodeQueue.push(neighbor);
                    }
                }
            }
            
        }
        ~graphType(){
            for(nodeType *node : nodes){
                delete node;
            }
        }
};

int main(){
    graphType graph;

    nodeType* A = graph.insertNode(1);
    nodeType* B = graph.insertNode(2);
    nodeType* C = graph.insertNode(3);
    nodeType* D = graph.insertNode(4);
    nodeType* E = graph.insertNode(5);
    nodeType* F = graph.insertNode(6);

    graph.link(A, B);
    graph.link(B, C);
    graph.link(C, D);
    graph.link(B, D);
    graph.link(C, F);
    graph.link(A, F);
    graph.link(E, C);

    graph.breadthFirst(A);

    std::cout << std::endl;
    
    graph.depthFirst(A);

    return 0;
}