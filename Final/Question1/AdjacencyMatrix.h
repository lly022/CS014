#ifndef __ADJACENCYMATRIX_H__
#define __ADJACENCYMATRIX_H__

#include "Graph.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/*struct Node{
    int indexNum;
    vector <int> neighbors;
    string discoveredInDFS;
    string discoveredInBFS;
    Node *prev;
    Node (int);
};*/

class AdjacencyMatrix : public Graph {
    private:
        vector<vector<int>> vect;
    public:
        AdjacencyMatrix(string filename);
        int vertices() const;
        int edges() const;
        int distance(int i) const;
        string path(int i) const;
        void bfs(int);
        void dfs(int);
        void display() const;
        void dfsVisit(vector<string>&, int);


};

#endif // __ADJACENCYMATRIX_H__
