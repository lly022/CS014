#include <iostream>
#include <string>
#include <cstdlib>
#include <stack>
#include <fstream>
#include <sstream>
#include "arithmeticExpression.h"

using namespace std;

arithmeticExpression::arithmeticExpression(const string &infix){
  infixExpression = infix;
  root = 0;
}

void arithmeticExpression::buildTree(){
  //char keyLetter  = 'a';
  //string postfix = infix_to_postfix();
  //root = buildNode(postfix, keyLetter);
  /*stack<TreeNode*> s;
  string postfix = infix_to_postfix();
  if(postfix == ""){
    root = nullptr;
  }
  for(unsigned int i = 0; i < postfix.size(); i++){
    char keyLetter = 'b';
    if(postfix.at(i) != '+' || postfix.at(i) != '-' || postfix.at(i) != '*' || postfix.at(i) != '/'){
      TreeNode *node = new TreeNode(postfix.at(i), keyLetter);
      s.push(node);
      keyLetter++;
    }
    else{//operand
      TreeNode *node = new TreeNode(postfix.at(i), keyLetter);
      keyLetter++;
      node->right = s.top();
      s.pop();
      node->left = s.top();
      s.pop();
      s.push(node);
    }
  }
  root = s.top();*/
  string postfix = infix_to_postfix();
  stack<TreeNode *> s;
  char c;
  int keyNum = 'a';
  for(unsigned i = 0; i < postfix.size(); i++){
    char currKey = (char)keyNum;
    keyNum++;
    c = postfix.at(i);
    TreeNode *curr = new TreeNode(c, currKey);
    if(i == postfix.size()-1){
      root = curr;
    }
    if(c == '+' || c == '-' || c == '*' || c == '/'){
      curr->right = s.top();
      s.pop();
      curr->left = s.top();
      s.pop();
      s.push(curr);
    }
    else{
      s.push(curr);
    }
  }
}

/*TreeNode* arithmeticExpression::buildNode(const string &expr, char key){
  TreeNode *node = new TreeNode(expr.at(expr.size()-1), key);
  expr.pop_back();
  key++;
  TreeNode *right = nullptr;
  TreeNode *left = nullptr;
  if(node->data == '+' && node->data == '-' && node->data == '*' && node->data == '/'){
    right = buildNode(expr, key);
    key++;
    left = buildNode(expr, key);
  }
  return node;
}*/

void arithmeticExpression::infix(){
  infix(root);
}

void arithmeticExpression::infix(TreeNode *curr){
  if(curr == 0){
    return;
  }
  else{
    if(curr->right == 0 && curr->left == 0){
      cout << curr->data;
    }
    else{
      cout << "(";
      infix(curr->left);
      cout << curr->data;
      infix(curr->right);
      cout << ")";
    }
  }
}

void arithmeticExpression::prefix(){
  prefix(root);
}

void arithmeticExpression::prefix(TreeNode *curr){
  if(curr == 0){
    return;
  }
  else{
    if(curr->right == 0  && curr->left == 0){
      cout << curr->data;
    }
    else{
      cout << curr->data;
      prefix(curr->left);
      prefix(curr->right);
    }
  }
}

void arithmeticExpression::postfix(){
  postfix(root);
}

void arithmeticExpression::postfix(TreeNode *curr){
  if(curr==0){
    return;
  }
  else{
    if(curr->right ==0 && curr->left == 0){
      cout << curr->data;
    }
    else{
      postfix(curr->left);
      postfix(curr->right);
      cout << curr->data;
    }
  }
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

void arithmeticExpression::visualizeTree(ofstream &oFS, TreeNode *curr){
  if(curr->right == 0 && curr->left == 0){
    return;
  }
  oFS << "key" << curr->key << " -> key" << curr->left->key << ";" << endl;
  oFS << "key" << curr->key << " -> key" << curr->right->key << ";" << endl;
  visualizeTree(oFS, curr->left);
  visualizeTree(oFS, curr->right);
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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
