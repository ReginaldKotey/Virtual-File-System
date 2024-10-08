
#ifndef INODE_H
#define INODE_H
#include<cstdlib>
#include<string>
#include<ctime>
#include "vector.hpp"

using namespace std;
enum {File=0,Folder=1};

class Inode
{
  private:
    string name;				//name of the Inode
    bool type;					//type of the Inode 0 for File 1 for Folder
    unsigned int size;			//size of current Inode
    string cr_time; 			//time of creation
    Vector1<Inode*> children;	//Children of Inode
    Inode* parent; 				//link to the parent 

  public:
    Inode(string name, Inode* parent, bool type, int size, string cr_time) : name(name),type(type),size(size),cr_time(cr_time),parent(parent){
      this->name=name;
      this->type=type;
      this->size=size;
      this->cr_time=cr_time;
      this->parent=parent;
    }
    string getName()
    {
      return this->name;
    }
    string getTime()
    {
      return this->cr_time;
    }

  public:
    friend class VFS;
};
#endif