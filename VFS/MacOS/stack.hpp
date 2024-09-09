#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "vector.hpp"

using namespace std;

template <typename T>
class Stack1
{
  private: 
  Vector1<T> myStack;
  int size=0;
  int capacity=0;
  public:
  Stack1(){size = myStack.size();
          capacity = myStack.capacity();}
  ~Stack1(){
  
  }
  const T Top(){//returns last element
    return myStack.back();
  }
  void Pop(){//removes last elem
    if (isEmpty())throw underflow_error("Stack is empty!");
    myStack.erase(--size);
  }
  bool isEmpty(){//retunr true if stack is empyty
    return size == 0;
  }
  void push(T elem){//puts an element in the last place
    myStack.push_back(elem);
    size++;
  }
};

#endif