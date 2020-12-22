#include <iostream>
#include <string>
#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree(){
  root = nullptr;
}

void AVLTree::insert(const string &key){
  if(root == nullptr){ //if tree is empty
    Node *node = new Node(key); //create new node
    root = node; //make root new node
    node->parent = nullptr; //assign root's parent as null
    return;
  }
  bool foundNode = search(key); 
  Node *tempNode = nullptr;
  if(foundNode){
    tempNode = returnNode(root, key); //get node with same key
    tempNode->count = tempNode->count + 1; //increase count
    return; //stop, don't make new node
  }
  Node *curr = root;
  Node *node = new Node(key);
  while(curr != nullptr){//go through tree
    if(curr->data == key){
      curr->count = curr->count + 1;
    }
    if(node->data < curr->data){//if data is less than curr node
      if(curr->left == nullptr){ //if reach leaf node
        curr->left = node; //make leaf node's left child new node
        node->parent = curr; //update new node's parent pointer
        curr = nullptr; 
      }
      else{
        curr = curr->left; //have not found correct spot to insert, continue left
      }
    }
    else{ //if data is greater than curr node
      if(curr->right == nullptr){ //if reach leaf node
        curr->right = node; //make lead node's right child new node
        node->parent = curr; //update new node's parent pointer
        curr = nullptr;
      }
      else{
        curr = curr->right; //have not found correct spot to insert, continue right
      }
    }
  }
  node = node->parent; //to rebalance tree, set node to its parent
  while(node != nullptr){ //go through tree
    rebalanceTree(node); //rebalance tree with node
    node = node->parent; //move up a level
  }
}

Node* AVLTree::rebalanceTree(Node *curr){
  updateHeight(curr); //update height of curr
  if(balanceFactor(curr) == -2){ //if balance of curr is -2
    if (balanceFactor(curr->right) == 1){ //if balance of curr's right child is 1
      // Double rotation case.
      rotateRight(curr->right); //rotate curr's right child to the right
    }
    rotateLeft(curr); //rotate curr to the left
   }
   else if (balanceFactor(curr) == 2){//if balance is 2
      if (balanceFactor(curr->left) == -1){// if curr's left child's balance is -1
         // Double rotation case.
         rotateLeft(curr->left);//rotate curr's left child to the left
      }
      rotateRight(curr);// rotate curr to rht right
   }        
   return curr;
}

Node* AVLTree::rotateLeft(Node *node){
  Node *rightLeftChild = node->right->left;
  Node *newSubroot = nullptr;
  if(node->parent != nullptr){ //if node isn't root
    replaceChild(node->parent, node, node->right);//replace node's parent with node's right child
    newSubroot = node->right; //new subroot turns into node's right child
  }
  else{ //node passed in as parameter is root
    root = node->right; //old root's right child is now new root
    root->parent = nullptr; //set root's parent to nullptr
    newSubroot = node->right; //new subroot turns into node's right child
  }
  setChild(node->right, "left", node); //set node's right child's left pointer to node
  setChild(node, "right", rightLeftChild);//set node's right pointer to rightLeftChild
  return newSubroot; //new subroot
}

Node* AVLTree::rotateRight(Node *node){
  Node *leftRightChild = node->left->right;
  Node *newSubroot = nullptr;
  if(node->parent != nullptr){ //if node isn't root
    replaceChild(node->parent, node, node->left);//replace node's parent with node's left child
    newSubroot = node->left; //new subroot turns into node's left child
  }
  else{ //node passed in as parameter is root
    root = node->left; //old root's left child is now new root
    root->parent = nullptr; //set root's parent to nullptr
    newSubroot = node->left; //new subroot turns into node's left child
  }
  setChild(node->left, "right", node); //set node's left child's right pointer to node
  setChild(node, "left", leftRightChild);//set node's left pointer to leftRightChild
  return newSubroot; //new subroot
}

bool AVLTree::replaceChild(Node *par, Node *curr, Node*newChild){//replaces par with newChild
if(par->left == curr){ //checks to see which child to replace
  return setChild(par, "left", newChild); //sets parent's left child to newChild
}
else if (par->right == curr){//checks to see which child to replace
  return setChild(par, "right", newChild); //sets parent's right child to newChild
}
return false; //if curr is not par's left or right child
}

bool AVLTree::setChild(Node *par, string whichChild, Node *child){
  if(whichChild != "left" && whichChild != "right"){ //correct input
    return false;
  }
  if(whichChild == "left"){ //if "left"
    par->left = child; //set parent's left child to child
  }
  else{ //if "right"
    par->right = child; //set parent's right child to child
  }
  if(child != nullptr){ 
    child->parent = par; //update child's parent to new parent 
  }
  updateHeight(par); //update height of parent 
  return true;
}

void AVLTree::updateHeight(Node *curr){
  int leftHeight = -1;
   if (curr->left != nullptr){ //as long as left child exists
      leftHeight = curr->left->height; //get height of left child
   }
   int rightHeight = -1;
   if (curr->right != nullptr){//as long as right child exists
      rightHeight = curr->right->height; //get height of right child
   }
   curr->height = max(leftHeight, rightHeight) + 1; //node's height = max of left child's height and right child's height + 1(counting node itself)
}

bool AVLTree::search(const string &key) const{
  return search(root, key); //uses private helper function
}

bool AVLTree::search(Node *curr, const string &key) const{
  if(curr == nullptr){ //if root == nullptr, empty
    return false;
  }
  if(curr->data == key){ //if found
    return true;
  }
  else if(curr->data > key){ //if key less than current
    return search(curr->left, key); //move left and search again
  }
  else{//if key greater than current 
    return search(curr->right, key);//move right and search again
  }
}

Node* AVLTree::returnNode(Node *curr, const string &key) const{
  Node *foundNode = nullptr;
  if(curr == nullptr){ //if root == nullptr, empty
    return foundNode;
  }
  if(curr->data == key){ //if found
    foundNode = curr;
    return foundNode;
  }
  else if(curr->data > key){ //if key less than current
    return returnNode(curr->left, key); //move left and search again
  }
  else{//if key greater than current 
    return returnNode(curr->right, key);//move right and search again
  }
}

void AVLTree::rotate(Node *curr){//Implement four possible imbalance cases and update the parent of the given node.
  //recommended private helper function 
  //already taken care of in rebalanceTree(Node*)
}

int AVLTree::balanceFactor(Node *curr){
  int leftHeight = -1;
  if(curr->left != nullptr){//as long as left child exists
    leftHeight = curr->left->height; //get height of left side of node
  }
  int rightHeight = -1;
  if(curr->right != nullptr){//as long as right child exists
    rightHeight = curr->right->height; //get height of right side of node
  }
  return leftHeight - rightHeight; //balance = left height - right height
}

Node* AVLTree::findUnbalancedNode(Node *curr){//Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.
  //recommended private helper function
  //insert() always rebalances tree so there will never be an unbalanced node after insert() ends
}

void AVLTree::printBalanceFactors(){
  printBalanceFactors(root);
  cout << endl;
}

void AVLTree::printBalanceFactors(Node *curr){ //inorder traversal
  if(curr == nullptr){ //if tree is empty or base case: reach leaf node
    return;
  }
  printBalanceFactors(curr->left); //go down left most nodes
  printNode(curr); //print current node
  printBalanceFactors(curr->right); //go down right most nodes
}

void AVLTree::printNode(Node* curr){
  cout << curr->data << "(" << balanceFactor(curr) << "), ";
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}
