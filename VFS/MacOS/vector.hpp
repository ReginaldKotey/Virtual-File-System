#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

template <typename T>
class Vector1
{
  private:
    T *data;						//pointer to int(array) to store elements
    int v_size;//current size of vector (number of elements in vector)
    int v_capacity;					//capacity of vector
  public:
    Vector1(int cap=1){data=new T[cap];
     v_size=0;
     v_capacity=cap;}			//Constructor
    ~Vector1(){delete []data;}				//Destructor
    int size() const{return v_size;}			//Return current size of vector
    int capacity() const{return v_capacity;}		//Return capacity of vector
    bool empty() const{return v_size==0;} 			//Rturn true if the vector is empty, False otherwise
    const T& front(){if(empty())throw underflow_error("Vector is empty!");
      return data[0];}				//Returns reference of the first element in the vector
    const T& back(){if(empty())throw underflow_error("Vector is empty!");
      return data[v_size-1];}				//Returns reference of the Last element in the vector
    void push_back(T element){insert(v_size,element);}		//Add an element at the end of vector
    void insert(int index, T element){if(index>size()||index<0){throw underflow_error("Index is Out of Range");}
       if(v_capacity==v_size+1){resize();}
          
       if(index==v_size){data[v_size]=element;v_size++;}
       else{
       for(int i=size()-1;i>=index;i--){
          data[i+1]=data[i];
       }
       data[index]=element;
       v_size++;
       }
    } //Add an element at the index 
  void erase(int index){
    if(empty())throw underflow_error("Vector is empty!");
    if(index>=size()||index<0)throw underflow_error("Index is Out of Range");
    if(index==size()-1){
       v_size--;
   }
   else{
     for(int i=index;i<size()-1;i++){
      data[i]=data[i+1];
     }
     v_size--;
   }}			//Removes an element from the index
  T& operator[](int index){if(empty())throw underflow_error("Vector is empty!");
    if(index>=size()||index<0)throw underflow_error("Index is Out of Range");
    return data[index];}			//Returns the reference of an element at given index
  T& at(int index){if(empty())throw underflow_error("Vector is empty!");
    if(index>=size()||index<0)throw underflow_error("Index is Out of Range");
    return data[index];} 				//return reference of the element at given index
  void shrink_to_fit(){T* temp= new T[v_size];
    for(int i=0;i<v_size;i++){
      temp[i]=data[i];
    }
    delete []data;
    data=temp;}			//Reduce vector capacity to fit its size
  void display(){for(int i=0;i<v_size-1;i++){
    cout<<data[i]<<",";
    }
    cout<<data[v_size-1]<<endl;}
  void resize(){
      v_capacity*=2;//multiplies the capacity by two and makes it new capacity
     T* temp= new T[v_capacity];
     for(int i=0;i<v_size;i++){
        temp[i]=data[i];
     }
     delete []data;
     data=temp;}
  void swap(int i, int b){
    T temp;
    temp=data[i];
    data[i]=data[b];
    data[b]=temp;
  }
    public:
    friend class Stack;
};
#endif