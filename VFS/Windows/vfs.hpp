#ifndef VFS_H
#define VFS_H
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<fstream>
#include "inode.hpp"
#include "queue.hpp"
#include "stack.hpp"

using namespace std;

class VFS
{
  private:
    Inode *root;				//root of the VFS
    Inode *curr_inode;			//current iNode
    Inode *prev_inode;			//previous iNode
    Queue<Inode*> bin;			//bin containing the deleted Inodes
    Queue<string> bin_paths;	//paths of the items in bin

  public:	 	
    //Required methods
    VFS();	
    ~VFS();
    void help();						
    string pwd(Inode* point=nullptr);
    void ls();						
    void mkdir(string folder_name);
    void touch(string file_name, unsigned int size);
    void cd(string path);
    void rm(string file_name);
    void size(string path);
    void showbin();
    void emptybin();
    void exit();

    //Optional methods
    void find(string name);
    void mv(string file, string folder);
    void recover();

    //Optional helper methods
    void load(ifstream &fin);				//Helper method to load the vfs.dat
    Inode* getNode(string path);			//Helper method to get a pointer to iNode at given path
    Inode* getChild(Inode *ptr, string childname);	//returns a specific child of given Inode
    bool find_helper(Inode *ptr, string name);		//recursive method to check if a given child is present under specific Inode or not
    int updateSize(Inode *ptr);					//re-calculatre the size of an Inode and its parents
    void write(ofstream &fout, Inode *ptr);			//traverse and write recrusively the vfs data
    string getTime();								//return system time as an string
    bool ispath(string path);
    void lssort(Inode* point=nullptr);
    void preOrderTraversal(Inode* node,string name);
};
//===========================================================
#endif