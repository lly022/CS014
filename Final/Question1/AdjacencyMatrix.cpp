#include "AdjacencyMatrix.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix(string filename){
  int v1;
  int v2;
  int v3;
	ifstream IFS;
	IFS.open(filename);
	if(!IFS){
		cout << "Could not open " << filename << endl;
		return;
	}
	IFS >> v1;
	vect = vector<vector<int> >(v1, vector<int>(v1, 0));
  _previous = vector<int>(v1, -1);
	_distances = vector<int>(v1, INT_MAX);
	while(IFS >> v2){
    IFS >> v3;
		vect.at(v2).at(v3) = 1;
	}
}

int AdjacencyMatrix::vertices() const{
	if(vect.size() != 0){
		return vect.size();
  }
  return 0;
}

int AdjacencyMatrix::edges() const{
  int edgeCount = 0;
	if(vect.size() == 0){
		return 0;
  }
	for(unsigned int i = 0; i < vect.size(); i++) {
		for(unsigned int j = 0; j < vect.size(); j++){
			if(vect.at(i).at(j) != 0){
				edgeCount++;
			}
		}
	}
	return edgeCount;
}

int AdjacencyMatrix::distance(int i) const{
	return _distances.at(i);
}

string AdjacencyMatrix::path(int i) const{
	stack<int> completeSteps;
	int prevIter = i;
	while (prevIter != -1) {
		completeSteps.push(prevIter);
		prevIter = _previous.at(prevIter);
	}
	string steps = "{";
	while (!completeSteps.empty()) {
		int temp = completeSteps.top();
		completeSteps.pop();
		steps += to_string(temp);
		if(completeSteps.empty()){
        steps = steps + "}";
    }
    else{
      steps = steps + "->";
    }
	}
	return steps;
}

// Overall runtime complexity: O(V^2), V = number of vertices in graph
// Overall space complexity: O(V^2), V = number of vertices in graph
void AdjacencyMatrix::bfs(int startNode){
	queue<int> q; //O(1)
  _previous = vector<int>(vertices(), -1); //O(V)
	_distances = vector<int>(vertices(), INT_MAX); //O(V)
  vector<string> discoverColor = vector<string>(vertices(), "White"); //O(V)
  _previous.at(startNode) = -1; //O(1)
	discoverColor.at(startNode) = "Gray"; //O(1)
  _distances.at(startNode) = 0; //O(1)
	q.push(startNode); //O(1)
	while(!q.empty()){ //O(V)
		int front = q.front(); //O(1)
		for(unsigned i = 0; i < vect.at(front).size(); i++){ //O(n) n is number of vertices
			if(vect.at(front).at(i) == 1 && discoverColor.at(i) == "White" ){ //O(1)
        q.push(i); //O(1)
        discoverColor.at(i) = "Gray"; //O(1)
        _previous.at(i) = front; //O(1)
				_distances.at(i) = _distances.at(front) + 1; //O(1)
			}
		}
		discoverColor.at(front) = "Black"; //O(1)
    q.pop(); //O(1)
	}
}

// Overall runtime complexity: O(V^2), V = number of vertices in graph
// Overall space complexity: O(V^2), V = number of vertices in graph
void AdjacencyMatrix::dfs(int startNode){
  _previous = vector<int>(vertices(), -1); // O(V)
  _distances = vector<int>(vertices(), INT_MAX); //O(V)
  _distances.at(startNode) = 0; //O(1)
	_previous.at(startNode) = -1; //O(1)
	vector<string> discoverColor = vector<string>(vertices(), "White"); //O(V)
	discoverColor.at(startNode) = "Gray"; //O(1)
	dfsVisit(discoverColor, startNode); //O(V^2)
}

void AdjacencyMatrix::dfsVisit(vector<string>& discoverColor, int index){
	discoverColor.at(index) = "Gray"; //O(1)
	for(int i = 0; i < vect.at(index).size(); i++){//O(V)
		if(vect.at(index).at(i) == 1 && discoverColor.at(i) == "White") {//tO(1)
      discoverColor.at(i) = "Gray"; //O(1)
			_previous.at(i) = index; //O(1)
      _distances.at(i) = _distances.at(index) + 1; //O(1)
			dfsVisit(discoverColor, i);//O(V)
		}
	}
	discoverColor.at(index) = "Black"; //O(1)
}

void AdjacencyMatrix::display() const{
  cout << "---Testing display()---" << endl;
  int count = 0;
  for(int i = 0; i < vect.size(); i++){
    for(int j = 0; j < vect.size(); j++){
      count++;
      if(count == 9){
        cout << vect.at(i).at(j) << "\n";
        count = 0;
      }
      cout << vect.at(i).at(j) << " ";
    }
  }
  cout << endl;
}
