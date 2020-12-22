#include "Jug.h"
using namespace std;

Vertex::Vertex(int amA, int amB){
  amountA = amA;
  amountB = amB;
  previous = -1;
  distance = INT_MAX;
  unvisited = false;
}

Jug::Jug(int Ca,int Cb,int N,int cfA,int cfB,int ceA,int ceB,int cpAB,int cpBA){
  this->Ca = Ca;
  this->Cb = Cb;
  this->N = N;
  this->cfA = cfA;
  this->cfB = cfB;
  this->ceA = ceA;
  this->ceB = ceB;
  this->cpAB = cpAB;
  this->cpBA = cpBA;
}

Jug::~Jug(){}

int Jug::solve(string &solution){
  if(Ca < 1 || Cb < 1 || Cb < Ca || N < 0 || Cb < N || Cb > 1000 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0){ //checking valid inputs
    solution = "";
    return -1;
  }
  Vertex start(0,0);
  vertices.push_back(start);
  buildgraph.push(0);
  graph(); 
  string success;
  success = dijkstra();
  if(success.empty()){
    return 0;
  }
  while(!steps.empty()){
    solution += (steps.top() + "\n");
    steps.pop();
  }
  solution += success;
  return 1;
}

void Jug::graph(){
  while(!buildgraph.empty()){
    bool found = false;
    unsigned int curr = buildgraph.top(); //curr is "vertex" on top of stack-last in first out
    buildgraph.pop(); 
    for(unsigned i = 0; i < visited.size(); i++){
      if(curr == visited.at(i)){ //search for curr is visited vector
        found = true;
        break;
      }
    }
    if(!found){//if curr isn't already visited
      visited.push_back(curr); //add to visited, build all possibilities of graph onto curr
      buildgraph.push(fillA(curr));
      buildgraph.push(fillB(curr));
      buildgraph.push(emptyA(curr));
      buildgraph.push(emptyB(curr));
      buildgraph.push(pourAB(curr));
      buildgraph.push(pourBA(curr));

    }
  }
}

unsigned int Jug::fillA(unsigned int curr){
  unsigned int index;
  bool found = false;
  Vertex neighbor(Ca, vertices.at(curr).amountB);
  for(unsigned int i = 0; i < vertices.size(); i++){//search for same vertex in graph that already exists
    if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == neighbor.amountB){
      index = i;
      found = true;
      break;
    }
  }
  pair<unsigned int, string> p;
  if(found){ //if there exists some vertex that has same amountA, amountB as curr, make a pair witht that vertex's index
    p = make_pair(index, "fill A");
  }
  else{ //if it doesn't exist
    vertices.push_back(neighbor); //it's new, add to vector of vertices
    p = make_pair(vertices.size()-1, "fill A"); //make pair with vertex's index(always last)
  }
  vertices.at(curr).neighbors.push_back(p); //curr vertex now has a "Fill A" neighbor
  return vertices.at(curr).neighbors.back().first; //return newly added pair's first(index of vertex that has same amountA and amountB(index of curr's "Fill A" neighbor))
}

unsigned int Jug::fillB(unsigned int curr){
  unsigned int index;
  bool found = false;
  Vertex neighbor(vertices.at(curr).amountA, Cb);
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == neighbor.amountB){
      found = true;
      index = i;
      break;
    }
  }
  pair<unsigned int, string> p;
  if(found){
    p = make_pair(index, "fill B");
  }
  else{
    vertices.push_back(neighbor);
    p = make_pair(vertices.size()-1, "fill B");
  }
  vertices.at(curr).neighbors.push_back(p);
  return vertices.at(curr).neighbors.back().first;
}

unsigned int Jug::emptyA(unsigned int curr){
  unsigned int index;
  bool found = false;
  Vertex neighbor(0, vertices.at(curr).amountB);
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(vertices.at(i).amountA == 0 && vertices.at(i).amountB == neighbor.amountB){
      found = true;
      index = i;
      break;
    }
  }
  pair<unsigned int, string> p;
  if(found){
    p = make_pair(index, "empty A");
  }
  else{
    vertices.push_back(neighbor);
    p = make_pair(vertices.size()-1, "empty A");
  }
  vertices.at(curr).neighbors.push_back(p);
  return vertices.at(curr).neighbors.back().first;
}

unsigned int Jug::emptyB(unsigned int curr){
  unsigned int index;
  bool found = false;
  Vertex neighbor(vertices.at(curr).amountA, 0);
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == 0){
      found = true;
      index = i;
      break;
    }
  }
  pair<unsigned int, string> p;
  if(found){
    p = make_pair(index, "empty B");
  }
  else{
    vertices.push_back(neighbor);
    p = make_pair(vertices.size()-1, "empty B");
  }
  vertices.at(curr).neighbors.push_back(p);
  return vertices.at(curr).neighbors.back().first;
}

unsigned int Jug::pourAB(unsigned int curr){
  unsigned int index;
  bool found = false;
  int neighborAAmount = vertices.at(curr).amountA;
  int neighborBAmount = vertices.at(curr).amountB;
  while(neighborAAmount > 0 && neighborBAmount < Cb){
    neighborAAmount--;
    neighborBAmount++;
  }
  Vertex neighbor(neighborAAmount, neighborBAmount);
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == neighbor.amountB){
      found = true;
      index = i;
      break;
    }
  }
  pair<unsigned int, string> p;
  if(found){
    p = make_pair(index, "pour A B");
  }
  else{
    vertices.push_back(neighbor);
    p = make_pair(vertices.size()-1, "pour A B");
  }
  vertices.at(curr).neighbors.push_back(p);
  return vertices.at(curr).neighbors.back().first;
}

unsigned int Jug::pourBA(unsigned int curr){
  unsigned int index;
  bool found = false;
  int neighborAAmount = vertices.at(curr).amountA;
  int neighborBAmount = vertices.at(curr).amountB;
  while(neighborAAmount < Ca && neighborBAmount > 0){
    neighborAAmount++;
    neighborBAmount--;
  }
  Vertex neighbor(neighborAAmount, neighborBAmount);
  for(unsigned int i = 0; i < vertices.size(); i++){
    if(vertices.at(i).amountA == neighbor.amountA && vertices.at(i).amountB == neighbor.amountB){
      found = true;
      index = i;
      break;
    }
  }
  pair<unsigned int, string> p;
  if(found){
    p = make_pair(index, "pour B A");
  }
  else{
    vertices.push_back(neighbor);
    p = make_pair(vertices.size()-1, "pour B A");
  }
  vertices.at(curr).neighbors.push_back(p);
  return vertices.at(curr).neighbors.back().first;
  
}

string Jug::dijkstra(){
  for(unsigned int i = 0; i < vertices.size(); i++){
      if(vertices.at(i).amountA == 0 && vertices.at(i).amountB == N){ //found goal vertex
        break;
      }
      else if(i == vertices.size() - 1){ //if get to end of all vertices and haven't found goal vertex, goal vertex doesn't exist, return empty string
        return "";
      }
  }
  //if goal vertex exists
  vector<Vertex *> unvisited;
  unsigned index;
  for(unsigned i = 0; i < vertices.size(); i++){//fill unvisited vertices vector with vertex pointers
    Vertex *pointer = &vertices.at(i);
    unvisited.push_back(pointer);
  }
  unvisited.at(0)->distance = 0; //distance from start to start = 0
  while(!unvisited.empty()){
    unsigned int minIndex = 0;  
    for(unsigned int i = 0; i < unvisited.size(); i++){ //find unvisited vertex that has shortest distance
      if(unvisited.at(i)->distance < unvisited.at(minIndex)->distance){
        minIndex = i;
      }
    }
    for(unsigned int i = 0; i < vertices.size(); i++){ //keep track of vertices index that's the same as the shortest path index in unvisited
      if(vertices.at(i).amountA == unvisited.at(minIndex)->amountA && vertices.at(i).amountB == unvisited.at(minIndex)->amountB){
        index = i;
      }
    }
    for(unsigned i = 0; i < unvisited.at(minIndex)->neighbors.size(); i++){
      unsigned int other = unvisited.at(minIndex)->distance + getCost(unvisited.at(minIndex)->neighbors.at(i).second);      
      if(vertices.at(unvisited.at(minIndex)->neighbors.at(i).first).distance > other){
        vertices.at(unvisited.at(minIndex)->neighbors.at(i).first).distance = other;
        vertices.at(unvisited.at(minIndex)->neighbors.at(i).first).previous = index;
      }
    }
    unvisited.erase(unvisited.begin() + minIndex); //pop off vertex with shortest distance
  }
  for(unsigned int i = 0; i < vertices.size(); i++){ //searching for vertex of all vertices for goal vertex(also happens to be shortest after top part)
    if(vertices.at(i).amountA == 0 && vertices.at(i).amountB == N){
      index = i;      
      break;
    }
  }
  unsigned int shortestDist = vertices.at(index).distance;  
  while(vertices.at(index).previous != -1)
  {
    for(unsigned int i = 0; i < vertices.at(vertices.at(index).previous).neighbors.size(); i++){
      if(vertices.at(vertices.at(index).previous).neighbors.at(i).first == index){
        steps.push(vertices.at(vertices.at(index).previous).neighbors.at(i).second);        
        break;
      }
    }
    index = vertices.at(index).previous; //update index to trace back to prev vertex (eventually start vertex)
  }  
  stringstream s;
  s << shortestDist;  
  return "success " + s.str();
}

int Jug::getCost(string action) const{
  if(action == "fill A"){
    return cfA;
  }
  else if(action == "fill B"){
    return cfB;
  }
  else if(action == "empty A"){
    return ceA;
  }
  else if(action == "empty B"){
    return ceB;
  }
  else if(action == "pour A B"){
    return cpAB;
  }
  else{ //if action == "pour B A"
    return cpBA;
  }
}
