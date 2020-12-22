#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

class Node{
  public:
  Node *left;
  Node *right;
  Node *parent;
  string data;
  int count;
  int height;
  Node(const string &);

};

#endif
