#include <iostream>
#include <string>
#include "IntList.h"
using namespace std;

int main() {
cout << "--- Testing push_front() & empty() & << ---" << endl;
IntList list;

cout << "If list is empty, returns true (should be true): ";
if(list.empty()){
  cout << "true" << endl;
} 
else{
  cout << "false" << endl;
}

cout << "Adding 1" << endl;
list.push_front(1);
cout << "Adding 2" << endl;
list.push_front(2);
cout << "Adding 3" << endl;
list.push_front(3);
cout << "Adding 4" << endl;
list.push_front(4);
cout << "Adding 5" << endl;
list.push_front(5);

cout << "If list is empty, returns true (should be false): ";
if(list.empty()){
  cout << "true" << endl;
} 
else{
  cout << "false" << endl;
}

cout << "Printing list using <<: " << list << endl << endl;

cout << "--- Testing printReverse() ---" << endl;
cout << "List: ";
list.printReverse();
cout << endl << endl;

cout << "--- Testing pop_front() & pop_back() ---" << endl;
list.pop_front();
cout << "List after pop_front(): ";
cout << list;
cout << endl;
cout << "Adding front element, removed from pop_front()" << endl;
list.push_front(5);
list.pop_back();
cout << "List after pop_back(): ";
cout << list;
cout << endl << endl; 

cout << "--- Testing push_back() ---" << endl;
cout << "Adding 100 to back of list" << endl;
list.push_back(100);
cout << "List: ";
cout << list;

return 0;
}
