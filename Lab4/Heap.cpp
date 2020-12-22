#include "Heap.h"
#include <iostream>

using namespace std;

Heap::Heap(){
  //arr = new PrintJob*[MAX_HEAP_SIZE];
  numItems = 0;
}

void Heap::enqueue ( PrintJob* PJ){
  if(numItems < MAX_HEAP_SIZE){
    if(numItems == 0){
      arr[numItems] = PJ;
      numItems++;
    }
    else{
      int currPJ = numItems;
      while(currPJ > 0 && arr[(currPJ-1)/2]->getPriority() < PJ->getPriority()){ //while there's still a parent to go up to/reach correct pos
        arr[currPJ] = arr[(currPJ-1)/2];
        currPJ = (currPJ-1)/2; //keep going up by parent
      }
      arr[currPJ] = PJ; //
      numItems++;//increment size of array
    }
  }
}

void Heap::dequeue ( ){
  //PrintJob *temp = arr[0];
  if(numItems == 0){
    return;
  }
  arr[0] = arr[numItems-1];
  numItems--;
  int root = 0;
  trickleDown(root);
}

PrintJob* Heap::highest ( ){//return arr[0]?
  /*PrintJob *highestPJ = arr[0]; //assigned root
  int highestPriority = highestPJ->getPriority();
  int tempPriority = 0;
  for(int i = 0; i < numItems; i++){ //go through array
    PrintJob *tempPJ = arr[i]; //temp variable
    tempPriority = tempPJ->getPriority();
    if(tempPriority > highestPriority){ //reassign highestPJ->higher prior. found
      highestPJ = tempPJ;
    }
  }
  return highestPJ;*/
  return arr[0];
}

void Heap::print ( ){
  PrintJob *highestPJ = highest(); //gets highest prior. PJ using highest()
  cout << "Priority: ";
  cout << highestPJ->getPriority();
  cout << ", Job Number: ";
  cout << highestPJ->getJobNumber();
  cout << ", Number of Pages: ";
  cout << highestPJ->getPages();
  cout << endl;
}

void Heap::trickleDown(int pos){
  int temp = (2*pos)+1; //left child
  if((2*pos)+1 < numItems){ //base case if recursion causes out of bounds
    if((2*pos)+2 < numItems && arr[(2*pos)+2]->getPriority() > arr[(2*pos)+1]->getPriority()){
      temp = (2*pos)+2;
    }
    if(arr[pos]->getPriority() < arr[temp]->getPriority()){
      swap(pos, temp);
      trickleDown(temp);
    }
  }
}

void Heap::swap(int Pos1, int Pos2){
  PrintJob *tempPJ = arr[Pos1];
  arr[Pos1] = arr[Pos2];
  arr[Pos2] = tempPJ;
}
