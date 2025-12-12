#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


/* 
*Name: Spanning Graphs
*Author: Wesley Hixon
*Date Last Updated: 12/11/2025
*Purpose: Create a graph and generate a eulerian path/cycle using Fleury's Algorithm, if one exists
*/

class graphType{
    private:
        std::vector<std::vector<bool>> adjMatrix;

        void removeEdge(std::vector<std::vector<bool>> &adj, int A, int B){
            adj[A][B] = false;
            adj[B][A] = false;
        }

        void insertEdge(std::vector<std::vector<bool>> &adj, int A, int B){
            adj[A][B] = true;
            adj[B][A] = true;
        }

        // Finds the number of nodes accessible from a root node
        int depthFirstSum(int node, std::vector<std::vector<bool>> &adj){
            std::vector<bool> visited(adj.size(), false);
            int sum = 0;
            
            for(int i = 0; i < adj.size(); i++){
                if(adj[node][i]== true && visited[i] == false){
                    depthFirstSumRec(i, adj, visited, sum);
                }
            }
            return sum;
        }

        void depthFirstSumRec(int node, std::vector<std::vector<bool>> &adj, std::vector<bool> &visited, int &sum){
            visited[node] = true;
            sum += 1;

            for(int i = 0; i < adj[node].size(); i++){
                if(adj[node][i] == true && visited[i] == false){
                    depthFirstSumRec(i, adj, visited, sum);
                }
            }
        }

        void FleuryRec(std::vector<std::vector<bool>> &adj, int node){
            std::cout << node;

            int adjacentCount = std::accumulate(adj[node].begin(), adj[node].end(), 0);

            if(adjacentCount == 0){
                return;
            }
            else if(adjacentCount == 1){
                std::cout << "->";
                for(int i = 0; i < adj.size(); i++){
                    if(adj[node][i] == true){
                        removeEdge(adj, node, i);
                        FleuryRec(adj, i);
                        break;
                    }
                }
            }
            // If two or more adjacent, only navigate thru edges that aren't bridges
            else{
                std::cout << "->";
                for(int i= 0; i < adj.size(); i++){
                    if(adj[node][i] == true && !bridge(node, i, adj)){
                        removeEdge(adj, node, i);
                        FleuryRec(adj, i);
                        break;
                    }
                }
            }
        }

        // Determines if the edge from A--B is a bridge
         bool bridge(int A, int B, std::vector<std::vector<bool>> adj){
            int beforeRemoval = depthFirstSum(A, adj);
            
            removeEdge(adj, A, B);
            int afterRemoval = depthFirstSum(A, adj);

            if(beforeRemoval == afterRemoval){
                return false;
            }
            else{
                return true;
            }
        } 

        
    public:

        graphType(int n){
            adjMatrix = std::vector<std::vector<bool>>(n, std::vector<bool>(n, false));
        }

        void printEdges(){
            for(std::vector<bool> a : adjMatrix){
                
                for(bool value : a){
                    std::cout << value << " ";
                }
                std::cout << std::endl;
            }
        }

        void insertEdge(int A, int B){
            insertEdge(adjMatrix, A, B);
        }

        void removeEdge(int A, int B){
            removeEdge(adjMatrix, A, B);
        }


        void printFleuryPath(){
            auto adj = adjMatrix;

            // Find the degrees of each node in the graph
            std::vector<int> nodeDegrees(adj.size(), 0);
            for(int i = 0; i < adj.size(); i++){
                nodeDegrees[i] = std::accumulate(adj[i].begin(), adj[i].end(), 0);
            }

            // Find the number of odd degrees
            int oddDegrees = 0;
            for(int degree : nodeDegrees){
                if(degree % 2 == 1){
                    oddDegrees++;
                }
            }

            if(oddDegrees != 0 && oddDegrees != 2){
                std::cout << "No Eulerian path or circuit";
                return;
            }

            // If 0 odd degree nodes, start at node 0
            if(oddDegrees == 0){
                FleuryRec(adj, 0);
            }
            // If 2 odd degree nodes, find an odd degree node and start there
            else{
                for(int node = 0; node < nodeDegrees.size(); node++){
                    if(nodeDegrees[node] % 2 == 1){
                        FleuryRec(adj, node);
                        break;
                    }
                }
            }
        }

        
};

int main(){

    graphType g(5);

    g.insertEdge(0, 1);
    g.insertEdge(1, 2);
    g.insertEdge(2, 0);   // triangle
    g.insertEdge(1, 3);   // bridge
    g.insertEdge(3, 4);   // tail

    g.printEdges();
    g.printFleuryPath();


    return 0;
}