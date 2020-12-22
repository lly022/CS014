#include <string>
#include <iostream>
#include "BSTree.h"

using namespace std;

BSTree::BSTree(){
  root = nullptr;
}

BSTree::~BSTree(){
  BSTDeconstructor(root);
}

void BSTree::BSTDeconstructor(Node *root) const{
  if(root){
    BSTDeconstructor(root->left);
    BSTDeconstructor(root->right);
    delete root;
  }
}

void BSTree::insert(const string &str){
  /*Node *newNode = new Node(str); //create new node
  if(root == nullptr){//if empty
    root = newNode; //make root new node
    newNode->count = 1; //increment count
  }
  Node *curr = root;
  while(curr != nullptr){
    if(newNode->S == curr->S){
      curr->count++;
    }
    else if(newNode->S < curr->S){
      curr = curr->left;
    }
    else{
      curr = curr->right;
    }
  }
  if(curr->left == nullptr){
    curr->left = newNode;
    newNode->count = newNode->count + 1;
  }
  else{
    curr->right = newNode;
    newNode->count = newNode->count + 1;
  }*/
  insert(root, str);
}

void BSTree::insert(Node *curr, const string &key){
  if(curr == nullptr){
    Node *newNode = new Node(key);
    root = newNode;
  }
  else{
  if(curr->S == key){
    curr->count = curr->count +1;
  }
  else if(curr->S < key){ //if key is smaller than curr->S
    if(curr->right == nullptr){
      Node *newNode = new Node(key);
      curr->right = newNode;
    }
    else{
      insert(curr->right, key);
    }
  }
  else{
    if(curr->left == nullptr){
      Node *newNode = new Node(key);
      curr->left = newNode;
    }
    else{
      insert(curr->left, key);
    }
  }
  }
}

void BSTree::remove(const string &key){
Node* par = nullptr;
Node* curr = root;
while(curr){
  if(curr->S == key){
    if(curr->count > 1){
      curr->count = curr->count -1;
        return;
    }
    if(!par){
      if(!curr->left && !curr->right){
        delete root;
        root = nullptr;
      }
      else if(curr->left && !curr->right){
        Node* tempNode = root->left;
          delete root;
          root = tempNode;
          return;
      }
      else if(curr->right && !curr->left){
        Node* tempNode = root->right;
        delete root;
        root = tempNode;
        return;
      }
      else{
        Node *succ = root->left;
        while (succ->right != nullptr){
          succ = succ->right;
        }
        string succString = succ->S;
        int sucCounter = succ->count;
        remove(succ->S);
        root->S = succString;
        root->count = sucCounter;
        return;
      }
    }
    else if(!curr->left && !curr->right) {
      if(!par){
        delete root;
        root = nullptr;
      }
      else if(par->left == curr){
        par->left = nullptr;
      }
      else{
        par->right = nullptr;
      }
    }
    else if(curr->left){
      Node *succ = curr->left;
      while (succ->right){
        succ = succ->right;
      }
      string succString = succ->S;
      remove(succ->S);
      curr->S = succString;
    }
    else if(curr->right){
      Node *succ = curr->right;
      while (succ->left){
        succ = succ->left;
      }
      string succString = succ->S;
      remove(succ->S);
      curr->S = succString;
      }
      return;
      }
      else if(curr->S < key){
        par = curr;
        curr = curr->right;
      }
      else{
        par = curr;
        curr = curr->left;
      }
    }
  return;
}

bool BSTree::search(const string &key) const{
  return search(root, key); //uses private helper function
}

bool BSTree::search(Node *curr, const string &key) const{
  if(curr == nullptr){ //if root == nullptr, empty
    return false;
  }
  if(curr->S == key){ //if found
    return true;
  }
  else if(curr->S > key){ //if key less than current
    return search(curr->left, key); //move left and search again
  }
  else{//if key greater than current 
    return search(curr->right, key);//move right and search again
  }
}

string BSTree::largest() const{
  string large = ""; //initially empty string
  if(root == nullptr){//if empty
    return large; //return empty string
  }
  large = root->S; //set large to root's string
  Node *curr = root;//set curr to root
  while(curr){//if curr != nullptr
    if(curr->S > large){ //if current's string is bigger than largest
      large = curr->S; //reset large to current's string
    }
    curr = curr->right;//move curr to right child
  }
  return large;
}

string BSTree::smallest() const{
  string small = ""; //initially empty string
  if(root == nullptr){//if empty
    return small; //return empty string
  }
  small = root->S; //set small to root's string
  Node *curr = root;//set curr to root
  while(curr){//if curr != nullptr
    if(curr->S < small){ //if curr's string is smaller than smallest
      small = curr->S; //reset small to curr's string
    }
    curr = curr->left;//move curr to left child
  }
  return small;
}

int BSTree::height(const string& key) const{
  Node *curr = root;
  while(curr){
    if(curr->S == key){
      return height(curr);
    }
    else{
      if(curr->S < key){
        curr = curr->right;
      }
      else{
        curr = curr->left;
      }
    }
  }
  return -1;
}

bool BSTree::foundNode(const string &key) const{
  Node *node = searchNode(key);
  if(node == nullptr){
    return false;
  }
  else{
    return true;
  }
}

Node* BSTree::searchNode(const string &key) const{
  Node *curr = root;
  Node *foundNode = nullptr;
  while(curr){
    if(curr->S == key){
      foundNode = curr;
    }
    curr = curr->left;
  }
  curr = root;
  while(curr){
    if(curr->S == key){
      foundNode = curr;
    }
    curr = curr->right;
  }
  return foundNode;
}

int BSTree::height(Node *curr) const{
  if(!curr){
    return -1;
  }
  int lHeight = height(curr->left);
  int rHeight = height(curr->right);
  if(lHeight > rHeight){
    return 1 + lHeight;
  }
  else{
    return 1 + rHeight;
  }
}

 void BSTree::printNode(Node* node) const{
   cout << node->S << "(" << node->count << "), ";
 }

void BSTree::inOrder() const{
  inOrder(root);
}

void BSTree::inOrder(Node *curr) const{
  if(curr == nullptr){//base case if empty/if can't go anymore
    return;
  }
  inOrder(curr->left); //keep going left, smallest->biggest
  printNode(curr);//once base case hits, print smallest->biggest
  inOrder(curr->right);//after finishing bigggest left subtree, move right, start again
}

void BSTree::preOrder() const{
  preOrder(root);
}

void BSTree::preOrder(Node *curr) const{
  if(curr == nullptr){//base case if empty/if can't go anymore
    return;
  }
  printNode(curr);//print curr first
  preOrder(curr->left); //keep going left, smallest->biggest
  preOrder(curr->right);//after finishing bigggest left subtree, move right, start again
}

void BSTree::postOrder() const{
  postOrder(root);
}

void BSTree::postOrder(Node *curr) const{
  if(curr == nullptr){//base case if empty/if can't go anymore
    return;
  }
  postOrder(curr->left); //keep going left, smallest->biggest
  postOrder(curr->right);//after finishing bigggest left subtree, move right, start again
  printNode(curr);//print curr last
}
