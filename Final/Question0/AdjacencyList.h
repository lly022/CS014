#ifndef __ADJACENCYLIST_H__
#define __ADJACENCYLIST_H__

#include "Graph.h"

#include <string>
#include <vector>
using namespace std;

struct Node{
    int indexNum;
    vector <int> neighbors;
    string discoveredInDFS;
    string discoveredInBFS;
    Node *prev;
    Node (int);
};

class AdjacencyList : public Graph {
    private:
      vector <Node*> Vertices;
      int numV;
      int numE;
    public:
        AdjacencyList(std::string filename);
        int vertices() const;
        int edges() const;
        int distance(int i) const;
        std::string path(int i) const;
        void bfs(int);
        void dfs(int);
        void dfsVisit(Node*);
        void display() const;

};

#endif // __ADJACENCYLIST_H__

