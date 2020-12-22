 #include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

Tree::Tree(){
  root = nullptr;
}

Tree::~Tree(){
  if(root){ //if tree not empty 
    deconstructTree(root); //deconstruct starting from root
  }
}

void Tree::deconstructTree(Node *curr){ //root is passed in
  if(curr == nullptr){ //base case: if can't go down anymore
    return;
  }
  deconstructTree(curr->left); //go down as far left as possible(left->middle->right)
  deconstructTree(curr->middle); //go down middle(left->middle->right)
  deconstructTree(curr->right); //go down right(left->middle->right)
  delete curr; //lastly, delete curr(parent)
}

bool Tree::isLeafNode(Node *n){
    if(n->left == nullptr && n->middle == nullptr && n->right == nullptr) {
        return true;
    }
    else {
        return false;
    }
}

void Tree::insert(const string &key){
 if(root == nullptr){ //if tree is empty
  root = new Node(key); //set root to new curr
  return; //exit
}
if(search(key)){ //if key is already in tree, exit
  return;
}
Node* curr = root;
while(1){
  //if curr has no children
  if(isLeafNode(curr)){
    if(curr->large.empty()){//if curr has one item
      if(key < curr->small){
        curr->large = curr->small; //set large to small
        curr->small = key;//set small to key
      }
      else{ //if key > curr->small
        curr->large = key; //set curr's large to key
      }
    }
   else{//if curr is full curr
    split(curr, key, nullptr, nullptr);
  }
    return; //exit
  }
  else{ //if curr has children
    if(key < curr->small){ 
      curr = curr->left; //continue left to find leaf curr
    }
    else if(key > curr->large){//if 2 curr and data > curr->large
      curr = curr->right; //continue down right to find leaf curr
    }
    else if(!(curr->large.empty())){ //if 3 curr, curr is full 
      if(key < curr->large){
        curr = curr->middle; //continue down middle to find leaf curr
      }
      else{// if key > curr->large
        curr = curr->right; //continue down right to find leaf curr
      }
    }
  }
}
}

void Tree::split(Node* curr, const string& key, Node* leftChild, Node* rightChild){
  Node* leftNode;
  Node* rightNode;
  string midString;
  //set leftNode, midString, rightNode
  if(key < curr->small){//if curr->small is midString
    leftNode = new Node(key);
    rightNode = new Node(curr->large);
    midString = curr->small;
  }
  else if(key > curr->large){ //if key > curr->large, curr->large is midString
    leftNode = new Node(curr->small);
    rightNode = new Node(key);
    midString = curr->large;
  }
  else{ //if key > curr->small && key < curr->large, key is midString
    leftNode = new Node(curr->small);
    rightNode = new Node(curr->large);
    midString = key;
  }

  if(curr->parent == nullptr){//if curr is root
    root = new Node(midString); //put midString in parent node/create new parent node
    root->left = leftNode; //reset pointers for root+children
    leftNode->parent = root;
    root->right = rightNode;
    rightNode->parent = root;
  }
  else if(curr->parent->large.empty()){//if parent is not full=>doesn't have 3 children
    if(midString < curr->parent->small){
      curr->parent->large = curr->parent->small; //reset curr's parent's small and large
      curr->parent->small = midString;
    }
    else{ //if midString > curr->parent->small
      curr->parent->large = midString;//put midString into parent node
    }
    if(leftNode->small > curr->parent->small){ // rotate right
      curr->parent->middle = leftNode; //set curr's parent's children
      curr->parent->right = rightNode;
    }
    else{ //if leftNode->small < curr->parent->small, rotate left
      curr->parent->left = leftNode; //set curr parent's children
      curr->parent->middle = rightNode;
    }
    //set parents
    leftNode->parent = curr->parent; 
    rightNode->parent = curr->parent;
  }
  else{ //if parent is full, trickle up by splitting
    split(curr->parent, midString, leftNode, rightNode);
  }
  //if curr is not a leaf curr, reset parent+children pointers
  if(!isLeafNode(curr)){
    if(leftNode->small > leftChild->small){ 
      leftNode->left = leftChild; 
      leftChild->parent = leftNode;
      leftNode->right = rightChild;
      rightChild->parent = leftNode;
      rightNode->right = curr->right;
      rightNode->right->parent = rightNode;
      rightNode->left = curr->middle;
      rightNode->left->parent = rightNode;
    }
    else if(rightNode->small < rightChild->small){//taking care of extra data
      leftNode->right = curr->middle;
      leftNode->right->parent = leftNode;
      leftNode->left = curr->left;
      leftNode->left->parent = leftNode;
      rightNode->right = rightChild;
      rightChild->parent = rightNode;
      rightNode->left = leftChild;
      leftChild->parent = rightNode;
    }
    else{
      leftNode->right = leftChild;
      leftChild->parent = leftNode;
      leftNode->left = curr->left;
      leftNode->left->parent = leftNode;
      rightNode->right = curr->right;
      rightNode->right->parent = rightNode;
      rightNode->left = rightChild;
      rightChild->parent = rightNode;
    }
  }
  delete curr; //curr doesn't matter anymore, delete
}

void Tree::remove(const string& key){
  if(!search(key)){ //if key isn't in tree, can't remove
    return;
  }
  Node* curr = search(root, key);
  Node* succ = curr;
  if(curr->right != nullptr){//if curr->middle is null
    succ = curr->right; //find inOrder successor through curr's right child if it's not null
  }
  else if(curr->middle != nullptr && curr->small == key){
    succ = curr->middle; //find inOrder successor through curr's middle child
  }
  while(!isLeafNode(succ)){ //finding actual inOrder successor
    succ = succ->left; //continue left until reach a leaf node
  }
  if(curr->small == key){ //reset to successor's data
    curr->small = succ->small;
    if(!succ->large.empty()){//if succ node is full
      succ->small = succ->large; //set succ's small to its large
      succ->large.clear(); //make large data empty
    }
    else{ //if succ's large is empty
      succ->small.clear(); //don't need small anymore
      fix(succ, nullptr); //fix succ node
    }
  }
  else{ //if curr->large == key
    if(curr != succ){
      curr->large = succ->small; //get rid of curr's large by replacing it with succ's small
        if(!succ->large.empty()){ //if succ node is a full node
          succ->small = succ->large; //set succ's small to succ's large
          succ->large.clear(); //don't need succ's large anymore
        }
        else{ //if succ's large is empty
          succ->small.clear(); //don't need succ's small anymore
          fix(succ, nullptr); //fic succ node
        }
    }
    else{ //if curr->large is key & curr node == swap node
      succ->large.clear(); //just make succ's large empty
    }
  }
}

void Tree::fix(Node* curr, Node* child){ //rebalance
if(curr == root){
    if(curr->left != nullptr || curr->right != nullptr){//if curr has at least one child
      root = child; //set root to child (parameter)
      child->parent = nullptr; //set child's parent to null
    }
    else{ //if curr has no children
      root = nullptr; //make tree empty
    }
    delete curr; 
    return;
  }
  if(curr->parent->left->large.empty() && curr->parent->right->large.empty()){ //if curr has no 3 node sibling
    if(curr->parent->right == curr){//if curr is its parent's right child
      curr = curr->parent; //set variable curr to original's parent
      if(curr->large.empty()){//if curr is not full node
        curr->left->large = curr->small; //reset data
        curr->small.clear(); //make curr's small empty
        delete curr->right; //don't need curr->right anymore
        curr->right = nullptr; //set node to nullptr
        if(child != nullptr){ //if child exists
          curr->left->middle = curr->left->right; //reset pointers
          curr->left->middle->parent = curr->left;
          curr->left->right = child;
          child->parent = curr->left;
        }
        fix(curr, curr->left); //fix again recurseively
      }
      else{ //if curr is a full node
        curr->right->large = curr->large; //reset data
        curr->large.clear();
        curr->right->small = curr->middle->small;
        if(child != nullptr){ //if child exists
          curr->right->right = child; //reset pointers
          child->parent = curr->right;
          curr->right->middle = curr->middle->right;
          curr->right->middle->parent = curr->right;
          curr->right->left = curr->middle->left;
          curr->right->left->parent = curr->right;
        }
      delete curr->middle; //don't need curr->middle anymore
      curr->middle = nullptr; //set node to nullptr
      }
    }
    else if(curr->parent->middle == curr){ //if curr is its parent's middle child
      curr = curr->parent; //set curr to its parent
      curr->left->large = curr->small; //reset data
      curr->small = curr->large;
      curr->large.clear();
      if(child != nullptr){ //if child exists
        curr->left->middle = curr->left->right; //reset pointers
        curr->left->middle->parent = curr->left;
        curr->left->right = child;
        child->parent = curr->left;
      }
    delete curr->middle; //don't need curr->middle anymore
    curr->middle = nullptr; //set node to nullptr
    }
    else{ //if curr->parent->left == curr,curr is left child of its parent
      curr = curr->parent; //set variable curr to original's parent
      curr->left->small = curr->small;
      if(curr->large.empty()){ //if curr is left child and its large is empty
        curr->left->large = curr->right->small; //reset data
        curr->small.clear(); //make curr's small empty
          if(child != nullptr){ //if child node exists
            curr->left->left = child; //reset pointers
            child->parent = curr->left;
            curr->left->middle = curr->right->left;
            curr->left->middle->parent = curr->left;
            curr->left->right = curr->right->right;
            curr->left->right->parent = curr->left;
          }
          delete curr->right; //don't need curr->right anymore
          curr->right = nullptr; //set node to nullptr
          fix(curr, curr->left); //fix again recursively
      }
      else{//if curr is left child and curr is a full node
        curr->left->large = curr->middle->small; //reset data
        curr->small = curr->large;
        curr->large.clear(); //make curr's large empty
        if(child != nullptr){ //if child node exists
          curr->left->left = child; //reset pointers
          child->parent = curr->left;
          curr->left->middle = curr->middle->left;
          curr->left->middle->parent = curr->left;
          curr->left->right = curr->middle->right;
          curr->left->right->parent = curr->left;
        }
        delete curr->middle; //don't need curr->middle anymore
        curr->middle = nullptr; //set node to nullptr
      }
    }
  }

  else{//curr has a 3 node sibling, can redistribute
    if(curr->parent->right == curr){ //curr is its parent's right child 
      curr = curr->parent; //set curr to its parent
      if(curr->large.empty()){ //if curr is not a full node
        curr->right->small = curr->small; //reset data
        curr->small = curr->left->large;
        curr->left->large.clear();
        if(child != nullptr){ //if child exists
          curr->right->right = child; //reset pointers
          child->parent = curr->right;
          curr->right->left = curr->left->right;
          curr->right->left->parent = curr->right;
          curr->left->right = curr->left->middle;
          curr->left->right->parent = curr->left;
          curr->left->middle = nullptr;
        }
      }
      else{ //if curr is a full node
        curr->right->small = curr->large; //reset data
        if(curr->middle->large.empty()){ //if curr's middle child is not a full node
          curr->large = curr->middle->small; //reset data
          curr->middle->small = curr->small;
          curr->small = curr->left->large;
          curr->left->large.clear();
          if(child != nullptr){ //if child exists
            curr->right->right = child; //reset pointers
            child->parent = curr->right;
            curr->right->left = curr->middle->right;
            curr->right->left->parent = curr->right;
            curr->middle->right = curr->middle->left;
            curr->middle->right->parent = curr->middle;
            curr->middle->left = curr->left->right;
            curr->middle->left->parent = curr->middle;
            curr->left->right = curr->left->middle;
            curr->left->right->parent = curr->left;
            curr->left->middle = nullptr;
          }
        }
        else{ //if curr's middle child is a full node
          curr->large = curr->middle->large; //reset data
          curr->middle->large.clear();
          if(child != nullptr){ //if child exists
            curr->right->right = child; //reset pointers
            child->parent = curr->right;
            curr->right->left = curr->middle->right;
            curr->right->left->parent = curr->right;
            curr->middle->right = curr->middle->middle;
            curr->middle->right->parent = curr->middle;
            curr->middle->middle = nullptr;
          }
        }
      }
    }
     else if(curr->parent->middle == curr){ //if curr is its parent's middle child
      curr = curr->parent; //set curr to its parent
      if(curr->right->large.empty()){ //if curr's right child is not a full node
        curr->middle->small = curr->small; //reset data
        curr->small = curr->left->large;
        curr->left->large.clear();
        if(child != nullptr){ //if child exists
          curr->middle->right = child; //reset pointers
          child->parent = curr->middle;
          curr->middle->left = curr->left->right;
          curr->middle->left->parent = curr->middle;
          curr->left->right = curr->left->middle;
          curr->left->right->parent = curr->left;
          curr->left->middle = nullptr;
        }
      }
      else{//if curr's right child is a full node
        curr->middle->small = curr->large; //reset data
        curr->large = curr->right->small;
        curr->right->small = curr->right->large;
        curr->right->large.clear();
        if(child != nullptr){ //if child exists
          curr->middle->left = child; //reset pointers
          child->parent = curr->middle;
          curr->middle->right = curr->right->left;
          curr->middle->right->parent = curr->middle;
          curr->right->left = curr->right->middle;
          curr->right->left->parent = curr->right;
          curr->right->middle = nullptr;
        }
      }
    }
    else{ //if curr->parent->left == curr, curr is its parent's left child
      curr = curr->parent; //set curr to its parent
      curr->left->small = curr->small; //reset data
      if(curr->large.empty()){ //if curr is not a full node
        curr->small = curr->right->small; //reset data
        curr->right->small = curr->right->large;
        curr->right->large.clear();
        if(child != nullptr){ //if child exists
          curr->left->left = child; //reset pointers
          child->parent = curr->left;
          curr->left->right = curr->right->left;
          curr->left->right->parent = curr->left;
          curr->right->left = curr->right->middle;
          curr->right->left->parent = curr->right;
          curr->right->middle = nullptr;
        }
      }
      else{ //if curr is a full node
        curr->small = curr->middle->small; //reset data
        if(curr->middle->large.empty()){ //if curr's middle child is not a full node
          curr->middle->small = curr->large; //reset data
          curr->large = curr->right->small;
          curr->right->small = curr->right->large;
          curr->right->large.clear();
          if(child != nullptr){ //if child exists
            curr->left->left = child; //reset pointers
            child->parent = curr->left;
            curr->left->right = curr->middle->left;
            curr->left->right->parent = curr->left;
            curr->middle->left = curr->middle->right;
            curr->middle->left->parent = curr->middle;
            curr->middle->right = curr->right->left;
            curr->middle->right->parent = curr->middle;
            curr->right->left = curr->right->middle;
            curr->right->left->parent = curr->right;
            curr->right->middle = nullptr;
          }
        }
        else{ //if curr's middle child is a full node
          curr->middle->small = curr->middle->large; //reset data
          curr->middle->large.clear();
          if(child != nullptr){ //if child exists 
            curr->left->left = child; //reset pointers
            child->parent = curr->left;
            curr->left->right = curr->middle->left;
            curr->left->right->parent = curr->left;
            curr->middle->left = curr->middle->right;
            curr->middle->left->parent = curr->middle;
            curr->middle->right = curr->right->left;
            curr->middle->right->parent = curr->middle;
            curr->right->left = curr->right->middle;
            curr->right->left->parent = curr->right;
            curr->right->middle = nullptr;
          }
        }
      }
    }
  }
}

bool Tree::search(const string &key) const{
  if(root == nullptr){//if tree is empty
    return false;
  }
  else{
    return search(root, key);
  }
}

Node* Tree::search(Node *curr, const string &key) const{
  if(curr != nullptr){ //if tree isn't empty
    if(key == curr->small){ //if key is curr's small
      return curr;
    }
    if(key < curr->small){ //if key is smaller, continue searching left
      return search(curr->left, key);
    }
    else if(!curr->large.empty()){//if curr's large isn't empty and key > curr->small
      if(key == curr->large){//if key is curr's large
        return curr;
      }
      else if(key > curr->large){ //key is > curr->large
        return search(curr->right, key);//continue searching down curr's right
      }
      else{ //if key < curr->large, key is between curr' small and large
        return search(curr->middle, key);//continue searching down middle
      }      
    }
    else{ // if curr->large.empty(), curr's large is empty and key > curr->small
      return search(curr->right, key); //continue searching to curr's right child(
    }
  }
  return nullptr; //if not found, return nullptr
}

void Tree::preOrder() const{
  preOrder(root);
  cout << endl;
}

void Tree::inOrder() const{
  inOrder(root);
  cout << endl;
}

void Tree::postOrder() const{
  postOrder(root);
  cout << endl;
}

void Tree::preOrder(Node *curr) const{
  if(curr != nullptr){ //if tree isn't empty
    if(curr->large.empty()){//curr's large is empty
      cout << curr->small << ", ";
      preOrder(curr->left);
      preOrder(curr->right);
    }
    else{//if curr's large isn't empty
      cout << curr->small << ", ";
      preOrder(curr->left);
      cout << curr->large << ", ";
      preOrder(curr->middle);
      preOrder(curr->right);
    }
  }
}

void Tree::inOrder(Node *curr) const{
  if(curr != nullptr){ //if tree isn't empty
    if(curr->large.empty()){ //if curr's large is empty
      inOrder(curr->left);
      cout << curr->small << ", ";
      inOrder(curr->right);
    }
    else{ //if curr's large isn't empty
        inOrder(curr->left);
        cout << curr->small << ", ";
        inOrder(curr->middle);
        cout << curr->large << ", ";
        inOrder(curr->right);
    }
  }
}

void Tree::postOrder(Node *curr) const{
  if(curr != nullptr){ //if tree isn't empty
    if(curr->large.empty()){ //if curr's large is empty
      postOrder(curr->left);
      postOrder(curr->right);
      cout << curr->small << ", ";
    }
    else{//if curr's large isn't empty
      postOrder(curr->left);
      postOrder(curr->middle);
      cout << curr->small << ", ";
      postOrder(curr->right);
      cout << curr->large << ", ";
    }
  }
}


