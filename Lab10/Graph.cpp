#include <string>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph(){}

Graph::Graph(ifstream& ifs)
{
  map<string, int> graph;
  int numNode;
  int numEdge;
  string tempString;
  ifs >> numNode >> numEdge;
  for(int i = 0; i < numNode; ++i){
    ifs >> tempString;
    Vertex tempV;
    tempV.label = tempString;
        vertices.push_back(tempV);
        graph[tempString] = i;
    }
  string string1;
  string string2;
  int cost;
  int index;
  for(int i = 0; i < numEdge; ++i){
    ifs >> string1 >> string2 >> cost;
    index = graph[string1];
    pair<int, int> p(graph[string2], cost);
    vertices.at(index).neighbors.push_back(p);
  }
}

Graph::~Graph()
{
    while(vertices.size() != 0)
    {
        vertices.pop_back();
    }
}

void Graph::output_graph(const string & fileName)
{
  ofstream ofs(fileName.c_str());
  if(!ofs.is_open()){
    cout << "Error Opening: " << fileName << endl;
    return;
  }
  ofs << "digraph G {" << endl;
  for(unsigned i = 0; i < vertices.size(); ++i){
    if(vertices.at(i).distance != INT_MAX){
      ofs << vertices.at(i).label << "[Label = \"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\"]" << endl;
    }
    if(!vertices.at(i).neighbors.empty()){
      list<pair<int, int>> :: iterator it = vertices.at(i).neighbors.begin();
      while(it != vertices.at(i).neighbors.end()){
        if(vertices.at(i).distance != INT_MAX){
          ofs << vertices.at(i).label << " -> " << vertices.at(it->first).label << endl;
        }
      it++;
      }
    }
  }
ofs << "}";
ofs.close();
string jpgFile = fileName.substr(0, fileName.size()-4) + ".jpg";
string command = "dot -tpng " + fileName + " -o " + jpgFile;
system(command.c_str());
}

void Graph::bfs()
{
  map<string, unsigned> graph;
  for(unsigned i = 0; i < vertices.size(); ++i){
    vertices.at(i).color = "WHITE";
    vertices.at(i).distance = INT_MAX;
    vertices.at(i).prev = 0;
    graph[vertices.at(i).label] = i;
  }
  vertices.at(0).color = "GRAY";
  vertices.at(0).distance = 0;
  queue<Vertex> q;
  q.push(vertices.at(0));
  Vertex curr;
  while(!q.empty()){
    curr = q.front();
    q.pop();
    list<pair<int,int>> :: iterator it = curr.neighbors.begin();
    while(it != curr.neighbors.end()){
      if(vertices.at(it->first).color == "WHITE"){
        vertices.at(it->first).color = "GRAY";
        vertices.at(it->first).distance = curr.distance + it->second;
        vertices.at(it->first).prev = &vertices.at(graph[curr.label]);
        q.push(vertices.at(it->first));
      }
    ++it;
    }
  }
}


int Graph::distance(const string &key) const{
  int dist = -1;
  for(unsigned i = 0; i < vertices.size(); i++){ //go through vertices vector
    if(key == vertices.at(i).label){ //if key = label
      dist = vertices.at(i).distance; //set dist to mv distance
    }
  }
  return dist; 
}

string Graph::previous(const string &key) const{
string prevVector = "";
for(unsigned i = 0; i < vertices.size(); i++){
  if(key == vertices.at(i).label){
    if(vertices.at(i).prev != nullptr){
      return vertices.at(i).prev->label;
    }
  }
}
return prevVector;
}
