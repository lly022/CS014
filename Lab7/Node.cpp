#include <string>
#include "Node.h"
using namespace std;

Node::Node(const string &newString){
  left = nullptr;
  right = nullptr;
  parent = nullptr;
  data = newString;
  count = 1;
  height = 0;
}
