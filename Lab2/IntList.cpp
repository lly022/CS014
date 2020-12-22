#include "IntList.h"
#include <string>
#include <iostream>

using namespace std;

IntList::IntList(){
  dummyHead = new IntNode(0); //create new IntNode
  dummyTail = new IntNode(0); //create new IntNode
  dummyHead->next = dummyTail; //head's next points to dummyTail
  dummyHead->prev = nullptr; //head's prev = null
  dummyTail->next = nullptr; //tail's next = null
  dummyTail->prev = dummyHead; //tail's prev points to dummyHead
}

IntList::~IntList(){
  IntNode *temp = dummyHead->next; //start at first real node
  while(temp != dummyTail){ //go until last real node
    delete temp; //delete current node
    temp = temp->next; //shift node to next node
  }
  dummyHead->next = dummyTail; //empty list = dummyHead's next = dummyTail
  dummyHead->prev = nullptr; //dummyHead's prev points to nothing
  dummyTail->next = nullptr; //dummyTail's next points to nothing
  dummyTail->prev = dummyHead; //dummyTail's prev = dummyHead
}

void IntList::push_front(int value){
  IntNode *newNode = new IntNode(value); //create new node
  IntNode *firstNode = dummyHead->next; //firstNode = real head
  newNode->next = firstNode; //newNode's next = former real head
  newNode->prev = dummyHead; //set newNode's prev to dummyHead
  dummyHead->next = newNode; //dummyHead's next is new real head
  firstNode->prev = newNode; //old real head's prev is now new real head
}

void IntList::pop_front(){
  if(empty()){ //do nothing
    return;
  }
  else{ //predNode(dummyHead)->currNode(real head)->sucNode
    IntNode *sucNode = dummyHead->next->next; //sucNode = second real node 
    IntNode *predNode = dummyHead; //predNode is dummyNode, currNode=real head 
    sucNode->prev = predNode; //set sucNode's prev to dummyNode
    predNode->next = sucNode; //set predNode's next to new real head
  }
}

bool IntList::empty() const{ //if no nodes between dummyHead and dummyTail
  return dummyHead->next == dummyTail; //dummyHead->prev = dummyHead
}

void IntList::pop_back(){
  if(empty()){ //do nothing 
    return;
  }
  else{ //predNode->currNode(real tail)->sucNode(dummyTail)
    IntNode *predNode = dummyTail->prev->prev; //predNode = 2nd to last node
    IntNode *sucNode = dummyTail; //sucNode is node after node to remove
    predNode->next = sucNode; //set predNode's next to dummyTail
    sucNode->prev = predNode;//set sucNode's prev to 2nd to last node
  }
}

ostream & operator<<(ostream &out, const IntList &rhs){
  if(!rhs.empty()){ //if list not empty
    IntNode *temp = rhs.dummyHead->next; //start at real head
    while(temp != rhs.dummyTail->prev){ //go until node before dummyTail
      out << temp->data << " "; //add data + space
      temp = temp->next; //shift one node
    }
    out << rhs.dummyTail->prev->data; //add last data w/ no space
  }
  return out;
}

void IntList::printReverse() const{
  if(empty()){ //do nothing
    return;
  }
  else{
    IntNode *temp = dummyTail->prev; //starrt at real tail 
    while(temp != dummyHead->next){//go until real head
      cout << temp->data << " "; //add data+space
      temp = temp->prev; //shift one node
    }
    cout << dummyHead->next->data; //add first data w/ no space
  }
}

void IntList::push_back(int value){ //predNode->newNode->sucNode
  IntNode *newNode = new IntNode(value); //create new node
  IntNode *predNode = dummyTail->prev; //predNode = real tail(last element)
  IntNode *sucNode = dummyTail; //sucNode is dummyTail
  predNode->next = newNode; //predNode's next is newNode
  newNode->prev = predNode; //set newNode's prev to predNode
  newNode->next = sucNode; //set newNode's next to dummyTail
  sucNode->prev = newNode; //dummyTail's prev is now newNode
}
