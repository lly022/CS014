#include <iostream>
#include <string>
#include <fstream>
#include "Node.h"

using namespace std;

class AVLTree{
  public:
    AVLTree();
    void insert(const string &); //Insert an item to the binary search tree and perform rotation if necessary.
    int balanceFactor(Node*);
    //Return the balance factor of a given node.
    void printBalanceFactors();
    //Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.
    bool search(const string &) const;
    void visualizeTree(const string &);
    //Generate dotty file and visualize the tree using dotty program. Call this function before and after rotation.
  private:
    Node *root;
    Node* rebalanceTree(Node*);
    void updateHeight(Node*);
    bool replaceChild(Node*, Node*, Node*);
    bool setChild(Node*, string, Node*);
    Node* findUnbalancedNode(Node*);
    //Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.
    bool search(Node*, const string &) const;
    Node* returnNode(Node*, const string &) const;
    void rotate(Node*);
    //Implement four possible imbalance cases and update the parent of the given node.
    Node* rotateLeft(Node *);
    //Rotate the subtree to left at the given node and returns the new subroot.
    Node* rotateRight(Node *);
    //Rotate the subtree to right at the given node and returns the new subroot.
    void printBalanceFactors(Node *);
    void printNode(Node*);
    void visualizeTree(ofstream &, Node *);
};
