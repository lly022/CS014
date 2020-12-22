#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

const int MAX_SIZE = 20;

template<typename T>
class stack{
  private:
    T data[MAX_SIZE];
    int size;
  public:
    stack();
    void push(T val);
    void pop();
    T top();
    bool empty();
};

template<typename T>
stack<T>::stack(){
  size = 0;
}

template<typename T>
void stack<T>::push(T val){
    if(size == MAX_SIZE){
      throw overflow_error("Called push on full stack.");
    }
    else{
      data[size] = val;
      size++;
    }
}

template<typename T>
void stack<T>::pop(){
  if(empty()){
      throw out_of_range("Called pop on empty stack.");
  }
  else{
    size--;
  }
}

template<typename T>
T stack<T>::top(){
    if(empty()){
      throw underflow_error("Called top on empty stack.");
    }
    else{
     return data[size-1];
    }
}

template<typename T>
bool stack<T>::empty(){
  return size == 0;
}
