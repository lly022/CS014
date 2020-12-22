#include "WordLadder.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <stack>  

using namespace std;

WordLadder::WordLadder(const string & dictFile){
  ifstream inFS;
  inFS.open(dictFile.c_str());
  if(!inFS.is_open()){
    cout << "No input file." << endl;
    return;
  }
  string word;
  while(inFS >> word){
    if(word.size() != 5){
      cout << "No input file." << endl;
      return;
    }
    dict.push_back(word);
  }
  inFS.close();
}

bool WordLadder::inDict(const string &str){//goes through entire dict list
  for(list<string>::iterator i = dict.begin(); i != dict.end(); i++){
    if(str == *i){ //if 2 strings are same
      return true; 
    }
  }
  return false; //if 2 strings are not same
}

bool WordLadder::oneLetterOff(const string &word1, const string &word2){
  int counter = 0; //counts number of unequal letters between strings
  for(unsigned i = 0; i < word1.size(); i++){//go through both strings
    if(word1.at(i) != word2.at(i)){//comparing letters
      counter++; //increment if different letters
    }
  }
  if(counter == 1){ //if only one letter is unequal
    return true;
  }
  else{//2 or more letters unequal
    return false;
  }
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile){
  /*ofstream oFS;
  oFS.open(outputFile.c_str());
  if(!oFS.is_open()){
    cout << "Error opening " << outputFile << endl;
    return;
  }
  if(!inDict(start) || !inDict(end)){//if start and end are in dict list
    oFS << "No Word Ladder Found." << endl;
    return;
  }
  if(start == end){//if start and end are equal, wordLadder = start
    oFS << start;
    return;
  }
  bool isWordLadder = false;
  queue<stack<string>> q; //create queue of stacks of strings
  stack<string> s;
  s.push(start); //add start onto stack
  q.push(s); //add stack onto queue
  while(!q.empty()){
    string topWord = q.front().top();
    for(list<string>::iterator i = dict.begin(); i != dict.end(); i++){
      if(oneLetterOff(*i, topWord)){
        stack<string> newStack;
        while(!q.front().empty()){
          newStack.push(q.front().top());
          q.front().pop();
        }
        newStack.push(*i);
        if(*i == end){
          while(!newStack.empty()){
            oFS << newStack.top() << endl;
            newStack.pop();
          }
          isWordLadder = true;
        }
        else{
          q.push(newStack);
          dict.erase(i);
          i--; //bc deleted original i, might skip words in dict list
        }
      }
    }
    q.pop();
  }
  if(q.empty() && !isWordLadder){
    oFS << "No Word Ladder Found." << endl;
  }*/

 ofstream oFS;
  oFS.open(outputFile.c_str());
  if(!oFS.is_open()){
    cout << "Error opening " << outputFile << endl;
    return;
  }
  queue<stack<string>> q;
  stack<string> s;
  string topWord;
  list<string>::iterator i;
  bool begin = false;
  bool finish = false;
  for(i = dict.begin(); i != dict.end(); i++){
    if(*i == start){
      begin = true;
    }
    if(*i == end){
      finish = true;
    }
  }
  if(!begin || !finish){
    cout << "Beginning and Last not found." << endl;
    return;
  }
  if(start == end){
    oFS << start;
    return;
  }
  s.push(start);
  q.push(s);
  dict.remove(start);
  stack<string> temp;
  while(!q.empty()){
    topWord = q.front().top();
    for(i = dict.begin(); i != dict.end(); i++){
      if(oneLetterOff(topWord, *i)){
        if(*i == end){
          q.front().push(end);
          while(!q.front().empty()){
            temp.push(q.front().top());
            q.front().pop();
          }
          while(!temp.empty()){
            oFS << temp.top() << " ";
            temp.pop();
          }
          return;
        }
        s = q.front();
        s.push(*i);
        q.push(s);
        i = dict.erase(i);
        i--; //erasing messes with i, may skip a word
      }
    }
    q.pop();
  }
 if(oFS.is_open()){
   oFS << "No Word Ladder Found.";
 }
 oFS.close();
}


 
