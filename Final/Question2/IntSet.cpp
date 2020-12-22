#include "IntSet.h"
#include <iostream>

using namespace std;

 IntSet::IntSet(){ // Default capacity is 1
  _capacity = 1;
  _table = new setRecord[1];
 }

 IntSet::IntSet(int n){
   _capacity = n;
   _table = new setRecord[1];
 }

 IntSet::IntSet(const IntSet &iS){ //copy constructor
   _capacity = iS._capacity;
   _table = iS._table;
  _comparisons = iS._comparisons;
  _size = iS._size;
 }

 void IntSet::insert(int key){// Insert the element into the set
  ++_comparisons;
  if(1 + _size > _capacity * 0.67){
    rehash(_capacity * 3);
  }
  bool freeSpot = false;
  int hashVal = key % _capacity;
  while(freeSpot == false){
    _comparisons++;
    if(_table[hashVal].value == key){
      return; //duplicate
    }
    else if(_table[hashVal].status != Occupied){
      freeSpot = true; //exit while loop
    }
    else{ //look for new spot
      hashVal = (hashVal + 1) % _capacity;
    }
  }
  //inserting
   _size++;
  _table[hashVal].status = Occupied;
  _table[hashVal].value = key; 
 }


 void IntSet::erase(int key){ // Erase the element from the set if it exists
  bool freeSpot = false;
  int hashVal = key % _capacity;  
  while(freeSpot == false){
    _comparisons++;
    if(_table[hashVal].status == Empty_since_start){
      return; //key DNE
    }
    else if(_table[hashVal].status == Occupied){
      if(_table[hashVal].value == key){
        freeSpot = true; //found, exit while loop
      }
      _comparisons++;
    }
    else{ //look for new spot
      hashVal = (hashVal + 1) % _capacity;
    }
  }
  _size--;
  _table[hashVal].status = Empty;
  _table[hashVal].value = -1;
 }

 void IntSet::rehash(size_t cap){
   int prevCap = _capacity;
   int rehashCap = cap;
   int temp;
   int hashVal;
   setRecord *s1 = new setRecord[rehashCap];
   for(int i = 0 ; i < prevCap; i++){
     if(_table[i].status == Occupied){
       bool freeSpot = false;
       hashVal = (hashVal+1) % rehashCap;
       temp = _table[i].value;
       while(freeSpot == false){
        if(s1[hashVal].status == Occupied){
          hashVal = (hashVal + 1) % rehashCap;
        }
        else{ //!= Occupied
          freeSpot = true;
        }
        _comparisons++;
       }
       s1[hashVal].status = Occupied;
       s1[hashVal].value = temp;
     }
    _comparisons++;
   }
  //delete[] _table;
  _table = s1;
  _capacity = cap;
 }

 int IntSet::comparisons(){ // Returns the number of camparisons from the last operation performed
  return _comparisons;
 }

 size_t IntSet::size() const{ // Returns the size
  return _size;
 }

 size_t IntSet::capacity() const{ // Returns the capacity
  return _capacity;
 }

 bool IntSet::empty() const{
   if(_size == 0){
     return true;
   }
   return false;
 }

 int IntSet::count(int key){ // Returns 1 if the key passed in exists in the set and 0 otherwise.
  int hashVal = key % _capacity;
  bool inSet = false;
  while(inSet == false){
    if(_table[hashVal].status == Empty_since_start){
      return 0;
    }
    else if(_table[hashVal].value == key){
      inSet = true;
    }
    hashVal = (hashVal + 1) % _capacity;
    _comparisons++;
  }
  return 1;
 }
