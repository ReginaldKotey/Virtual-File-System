#ifndef QUEUE_H
#define QUEUE_H
#include<cstdlib>
#include<stdexcept>

using namespace std;
template <typename T>

class Queue
{
  private:
    T *array;
    int capacity;	//Max Capacity of the Queue
    int size;		//current number of elements in the Queue
    int front;		//front of the Queue
    int rear;		//index where a new element will be added
  public:
    Queue(int capacity=10){
      array=new T[capacity];
      this->capacity=capacity;
      size=0;
      front=0;
      rear=0;
    }
    ~Queue(){
      delete []array;
    }
    void enqueue(T elem){//add elem at rear index
      if(isFull())throw overflow_error("Queue is Full!");
      array[rear]=elem;
      size++;
      rear=(rear+1)%capacity;
    } 
    T dequeue(){//removes elem and returns it
      if(isEmpty())throw underflow_error("Queue is Empty!");
      T temp= front_element();
      front=(front+1)%capacity;
      size--;
      return temp;
    }
    bool isEmpty(){
      return size==0;
    }
    bool isFull(){
      return size==capacity;
    }
    T front_element(){//returns front elem but does not remove anything
      if(isEmpty())throw underflow_error("Queue is Empty!");
      return array[front];
    }
    friend void display();
};
//================================================
#endif