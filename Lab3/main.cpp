#include <iostream>
#include <vector> 
#include <stdexcept>
using namespace std;

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
  unsigned int minIndex = index;
  for(unsigned i = index; i < vals.size(); i++){
    if(vals.at(i) < vals.at(minIndex)){
      minIndex = i;
      }
  }
  return minIndex;
}

template<typename T>
void selection_sort(vector<T> &vals){
  for(unsigned i = 0; i < vals.size(); i++){
    unsigned min = min_index(vals, i);
    T temp = vals.at(i);
    vals.at(i) = vals.at(min);
    vals.at(min) = temp;
  }
}

template<typename T>
void printVector(vector<T> &vals){
  for(unsigned i = 0; i < vals.size(); i++){
    cout << vals.at(i) << " ";
  }
  cout << endl;
}

template<typename T>
T getElement(vector<T> vals, int index){
  return vals.at(index);
}

int main() {
cout << "---Testing min_index()---" << endl;
vector<int> v1 {9, 7, 2, 5, 1};
vector<int> v2 {5, 8, 13, 1, 5, 10};
vector<int> v3 {8, 3, 9, 10, 6, 5, 1, 41};
vector<int> v4 {2, 1};
unsigned minIndex1 = min_index(v1, 0);
cout << "minIndex should be 4: " << minIndex1 << endl;
unsigned minIndex2 = min_index(v1, 3);
cout << "minIndex should be 4: " << minIndex2 << endl;
unsigned minIndex3 = min_index(v2, 0);
cout << "minIndex should be 3: " << minIndex3 << endl;
unsigned minIndex4 = min_index(v2, 4);
cout << "minIndex shoule be 4: " << minIndex4 << endl << endl;

cout << "---Testing selection_sort():---" << endl;
cout << "v1 before selection_sort(): ";
printVector(v1);
cout << "v1 after selection_sort(): ";
selection_sort(v1);
printVector(v1);
cout << "v2 before selection_sort(): ";
printVector(v2);
cout << "v2 after selection_sort(): ";
selection_sort(v2);
printVector(v2);
cout << "v3 before selection_sort(): ";
printVector(v3);
cout << "v3 after selection_sort(): ";
selection_sort(v3);
printVector(v3);
cout << "v4 before selection_sort(): ";
printVector(v4);
cout << "v4 after selection_sort(): ";
selection_sort(v4);
printVector(v4);
cout << endl;

 //Part B
    try{
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int size = vals.size();
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         if(index < 0 || index >= size){
           throw out_of_range(""); //can do "out of range exception occured"
         }
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
     }
    }
    catch(const out_of_range &excpt){
      cout << "out of range exception occured" << endl;
    }
    return 0;
}
