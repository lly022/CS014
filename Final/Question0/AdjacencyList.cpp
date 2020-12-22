#include "AdjacencyList.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

#define INT_MAX 2147483647

Node::Node(int index){
  indexNum = index;
  discoveredInDFS = "White";
  discoveredInBFS = "White";
}

AdjacencyList::AdjacencyList(string filename){
  numV = 0;
  numE = 0;
  ifstream IFS;
  int numN;
  int sourceNode;
  int sinkNode;
  IFS.open(filename);
  if(!IFS){
    cout << "Could not open file" << endl;
    return;
  }
  IFS >> numN;
  for(int i = 0; i < numN; i++){
    Node *n = new Node(i);
    Vertices.push_back(n);
    ++numV;
  }
  for(int j = 0; j < numN; j++){
    _previous.push_back(0);
    _distances.push_back(INT_MAX);
  }
  while(IFS >> sourceNode){
    IFS>> sinkNode;
    ++numE;
    Vertices.at(sourceNode)->neighbors.push_back(sinkNode);
  }
}

int AdjacencyList::vertices() const{
  unsigned int temp = numV;
  return temp;
}

int AdjacencyList::edges() const{
  unsigned int temp = numE;
  return temp;
}

int AdjacencyList::distance(int i) const{
  return _distances.at(i);
}

//{source->next->next->sink} with no whitespace
//{0->2->1}
string AdjacencyList::path(int i) const{
  string completeSteps;
  stack <int> steps;
  int sinkPrevious = _previous.at(i);
  if(i != 0){
    steps.push(i);
  }
  while(sinkPrevious != 0){
    steps.push(sinkPrevious);
    sinkPrevious = _previous.at(sinkPrevious);
  }
  steps.push(0);
  completeSteps = "{";
  while(!steps.empty() ){
    string topOfStack = to_string(steps.top());
    completeSteps = completeSteps + topOfStack;
    steps.pop();
      if(steps.empty()){
        completeSteps = completeSteps + "}";
      }
      else{
        completeSteps = completeSteps + "->";
      }
  }
  return completeSteps;
}

// Overall runtime complexity: O(V + E) , V = number of vertices in graph, E = number of edges in graph
// Overall space complexity: O(V)
void AdjacencyList::bfs(int startNode){
  queue <Node*> q; // O(1)
  q.push(Vertices.at(startNode)); // O(1)
  _distances.at(startNode) = 0; // O(1)
  Vertices.at(startNode)->discoveredInBFS = "Grey"; // O(1)
  while(!q.empty() ){ // O(V)
    Node *n = q.front(); // O(1)
    q.pop(); // O(1)
    for(unsigned int i = 0; i < n->neighbors.size(); i++){ // O(E)
      if(Vertices.at(n->neighbors.at(i))->discoveredInBFS == "White"){ // O(1)
        Vertices.at(n->neighbors.at(i))->discoveredInBFS = "Grey"; // O(1)
        _distances.at(n->neighbors.at(i)) = _distances.at(n->indexNum)  + 1; // O(1)
        _previous.at(n->neighbors.at(i)) = n->indexNum; // O(1)
        q.push(Vertices.at(n->neighbors.at(i))); // O(1)
      }
    }
    n->discoveredInBFS = "Black"; // O(1)
  }
}

// Overall runtime complexity: O(V + E), V = number of vertices in graph, E = number of edges in graph
// Overall space complexity: O(bm), m = length of longest path, b = total number of neighbors for every node(Vertex)
void AdjacencyList::dfs(int startNode){
  _distances.at(startNode) = 0; //O(1)
  for(unsigned int i = 0; i < Vertices.size(); i++){ //O(V) 
    Vertices.at(i)->discoveredInDFS = "White"; //O(1)
    Vertices.at(i)->prev = nullptr; //O(1)
  }
  for(unsigned int i = 0; i < Vertices.size(); i++){ //O(1)
    if(Vertices.at(i)->discoveredInDFS == "White"){ //O(1)
      dfsVisit(Vertices.at(i)); //O(E)
    }
  }
}

void AdjacencyList::dfsVisit(Node *n){
  n->discoveredInDFS = "Grey"; 
  for(unsigned int i = 0; i < n->neighbors.size(); i++){
    if(Vertices.at(n->neighbors.at(i))->discoveredInDFS == "White"){
      Vertices.at(n->neighbors.at(i))->prev = n;
      _distances.at(n->neighbors.at(i)) = _distances.at(n->indexNum) + 1;
        _previous.at(n->neighbors.at(i)) = n->indexNum;
      dfsVisit(Vertices.at(n->neighbors.at(i)));
    }
  }
  n->discoveredInDFS = "Black";
}


void AdjacencyList::display() const{
cout << "{ ";
  for(unsigned int i = 0; i < Vertices.size(); i++){
    for(unsigned int j = 0; j < Vertices.at(i)->neighbors.size(); j++){
      if(i >=  1 || j >= 1){
        cout << ", ";
      }
      cout << "(" << Vertices.at(i)->indexNum << "->" << Vertices.at(i)->neighbors.at(j) << ")";
    }
  }
  cout << " }" << endl;
}
