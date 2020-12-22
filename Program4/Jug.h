#ifndef JUG_H
#define JUG_H

//using stack and vector libraries -> www.cplusplus.com as reference
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

class Vertex{
  friend class Jug;
  public:
    Vertex(int, int);
  private:
    int amountA;
    int amountB;
    int previous;
    unsigned int distance;
    bool unvisited;
    vector<pair<unsigned int, string>> neighbors;
};


class Jug {
  public:
    Jug(int,int,int,int,int,int,int,int,int);
    ~Jug();
    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution);
  private:
    int Ca;
    int Cb;
    int N;
    int cfA;
    int cfB;
    int ceA;
    int ceB;
    int cpAB;
    int cpBA;
    stack<unsigned int> buildgraph;
    vector<unsigned int> visited;
    vector<Vertex> vertices;
    stack<string> steps;
    void graph();
    unsigned int fillA(unsigned int);
    unsigned int fillB(unsigned int);
    unsigned int emptyA(unsigned int);
    unsigned int emptyB(unsigned int);
    unsigned int pourAB(unsigned int);
    unsigned int pourBA(unsigned int);
    string dijkstra();
    int getCost(string) const;
};

#endif
