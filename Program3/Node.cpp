#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

Node::Node(){
  small = "";
  large = "";
  left = nullptr;
  middle = nullptr;
  right = nullptr;
  parent = nullptr;
}

Node::Node(const string &str){
  small = str;
  large = "";
  left = nullptr;
  middle = nullptr;
  right = nullptr;
  parent = nullptr;
}

Node::Node(const string &str, Node *p){
  small = str;
  large = "";
  left = nullptr;
  middle = nullptr;
  right = nullptr;
  parent = p;
}
