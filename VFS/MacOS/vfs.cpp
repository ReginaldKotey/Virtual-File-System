#include "vfs.hpp"

void VFS::help() {//this function print info about all the functions that can be used in the virtual file system
  cout << "pwd:                        prints the path of current inode" << endl;
  cout << "ls:                         prints the children of the current inode" << endl;
  cout << "mkdir <foldername>:         creates folder with foldername <foldername> under current folder"<< endl;
  cout << "touch <filename> <size>:    creates a file with filename <filename> and size <size>"<< endl;
  cout << "cd <foldername>:            changes the current inode to the specified folder"<< endl;
  cout << "cd..:                       changes current inode to its parent folder" << endl;
  cout << "cd:                         changes current inode to root" << endl;
  cout << "cd-:                       changes current inode to the previous working directory"<< endl;
  cout << "cd/my/path/name:            changes the current inode to the specified path if it exists"<< endl;
  cout << "find <node>:                returns the path of the file or folder if it exists"<< endl;
  cout << "mv <filename> <foldername>: moves a file under the current inode to foldername"<< endl;
  cout << "rm <node>:                  removes the specified folder or file and puts it in the bin which has a max size of 10"<< endl;
  cout << "size <node>:                returns the total size of the folder or file including all its subfolders "<< endl;
  cout << "emptybin:                   empties bin" << endl;
  cout << "showbin:                    shows the oldest node in the bin" << endl;
  cout << "recover:                    reinstates the oldest inode back from the bin to its old position"<< endl;
  cout << "exit:                       stops the program" << endl;
}
VFS::VFS() {//conctructor that creates the tree
  root = new Inode("/", nullptr, true, 0, getTime());//create a new node of size 0 and no parent with name / and assign it to the tree
  curr_inode = root;//point current node to the root
  prev_inode = nullptr;//set the previous node to null
}
string VFS::pwd(Inode *point) { // prins path of current node
  Inode *ctr = point;//assign point to the an inode variable ctr
  if (point == nullptr)//if point is null meaning nothing was passes as argument to the pwd function
    ctr = curr_inode;//assign the current node to ctr
  if (ctr == root) {//otherwise if ctr is pointing to the root just return /
    return "/";
  }
  Stack1<string> pathStack;//create a stack pathstack
  while (ctr != root) {//until we reach the root
    pathStack.push(ctr->getName());//push the name of the ctr
    ctr = ctr->parent;//assign ctr parent to ctr
  }
  string path;//create a string 
  while (!pathStack.isEmpty()) {//while the stack is not empty
    path += "/";//add / first 
    path += pathStack.Top();//add the last elem in the stack to path
    pathStack.Pop();//remove the first elem in the stack
  }
  return path;
}
void VFS::ls() {//this function prints out all the children of the current node
  if (curr_inode->type == false)//if the current node type is file throw error
    throw overflow_error("File has no subfolders or files!");
  lssort();//sort the children according to size
  for (int i = 0; i < curr_inode->children.size(); i++) {//go through all the children
    string filetype = "dir";// if it is a folder name filetype dir
    if (curr_inode->children[i]->type == false)//other if file name filetype file
      filetype = "file";
    cout << filetype << ", " << curr_inode->children[i]->name << ", "<< curr_inode->children[i]->size << " bytes, " << curr_inode->children[i]->getTime() << endl;
  //print the filetype, the name, the size, add bytes, and the time it was created
  }
}
void VFS::mkdir(string folder_name) {//thsi function makes folders
  if (curr_inode->type == false)//if the current not is in a file print error... we shouldnt be able to get the curr_inode into a file but i am jsut checking again
    throw overflow_error("Cannot create folder under file");
  Inode *temp = new Inode(folder_name, curr_inode, true, 10, getTime());//create a new Inode with size 10, name <foldername>, type folder and parent the current node
  temp->parent = curr_inode;
  curr_inode->children.push_back(temp);//add this new node to the children of the current node
}
void VFS::touch(string file_name, unsigned int size) {//this function makes files
  if (curr_inode->type == false)
    throw overflow_error("Cannot create folder under file");
  Inode *temp = new Inode(file_name, curr_inode, false, size, getTime());//this type size is size and filetype is file
  temp->parent = curr_inode;
  curr_inode->children.push_back(temp);
}
bool VFS::ispath(string path) {//this function checkes if the string is a path or a filename/foldername
  char checker;
  for (long unsigned int i = 0; i < path.length(); i++) {
    checker = path[i];
    if (checker == '/')//go through the string, if you find / return true meaning it is a path
      return true;
  }
  return false;//otherwise return false
}
void VFS::cd(string path) {//this function does wonders
  if (path == "..") {// if this is the case go to currinode's parent
    if (curr_inode == root)//throw error if we are at the root
      throw overflow_error("Cannot go up from root");
    prev_inode = curr_inode;//make the previous inode point to where we are before changing
    curr_inode = curr_inode->parent;
    return;
  } else if (path == "") {//if it is just cd, go to root
    prev_inode = curr_inode;//you know, same as before
    curr_inode = root;
    return;
  } else if (path == "-") {//if it is cd - go to the prev inode.
    Inode *temp_prev = curr_inode;//in this case first store the curr inode to a temp
    curr_inode = prev_inode;//take inode to the prev inode 
    prev_inode = temp_prev;//make the prev inode the temp
    return;
  } else if (ispath(path)) {//if it is a path as in cd /rekas
    if(!getNode(path)->type)throw underflow_error("can't cd into file");//if the path leads to a file throw an error
    prev_inode = curr_inode;
    curr_inode = getNode(path);//get the node of the path and assign it to the current path
    return;
  } else {//otherwise
    prev_inode = curr_inode;// make the prev inode the current onde 
    Inode *scanner = nullptr;
    for (int i = 0; i < curr_inode->children.size(); i++) {//go throw all the children if you find the folder, make it the current node
      scanner = curr_inode->children[i];
      if (scanner->getName() == path) {
        if (scanner->type == true) {
          curr_inode = scanner;
          return; // Exit the function if folder found
        } else {
          throw underflow_error("Cannot navigate into a file!");//throw error if it is a file
        }
        return;
      }
    }
  }
  // If the loop completes and the folder was not found
  throw underflow_error("Folder not found under this current folder!");
}

void VFS::rm(string file_name) {//this function removes a file/folder
  Inode *scanner = curr_inode->children[0];
  int fileindex = 0;
  for (int i = 0;
       scanner->getName() != file_name && i < curr_inode->children.size();//go through all the children, if you find the file/folder quit loop 
       i++) {
    scanner = curr_inode->children[i];
    fileindex = i;
  }
  if (scanner->getName() == file_name) {// if we found it
    bin.enqueue(scanner);//put in bin
    bin_paths.enqueue(pwd() + "/" + file_name);//put path in bin even though i dont use this
    curr_inode->children.erase(fileindex);//remove the child from the children vector
  } else {
    throw underflow_error("Folder not found under this current folder!");//if the child is not found print error
  }
}
void VFS::size(string path) {//this function gives us size of a file/folder
  if (ispath(path)) {//if path is a path
    Inode *control = getNode(path);//get the node from the path
    int totalsize = 0;
    totalsize += updateSize(control);//get the size from the updatesize function
    cout << "Total Size is " << totalsize <<" bytes"<< endl;//print the size
  } else if (!ispath(path)) {//if it is not a path
    if (curr_inode->children.size() == 0)//go through the children of the currnode and print the size of the child that has this name
      throw underflow_error("Folder is empty");//if the current node has not children print error
    Inode *scanner = curr_inode->children[0];
    int totalsize = 0;
    for (int i = 0;scanner->getName() != path && i < curr_inode->children.size(); i++) {
      scanner = curr_inode->children[i];
    }
    if (scanner->getName() == path) {
      totalsize += updateSize(scanner);
      cout << "Total Size is " << totalsize <<" bytes" <<endl;
    }
  } else {
    throw underflow_error("Folder not found under this current folder!");
  }
}
int VFS::updateSize(Inode *ptr) {//this is a recursize function that finds the size of the child
  int totalsize = ptr->size;//assign size of ptr passed to total size
  if (ptr->children.size() == 0) {
    return totalsize;//if child is a leave return the total size other go through his children till the last level
  }
  for (int i = 0; i < ptr->children.size(); i++) {
    totalsize += updateSize(ptr->children[i]);//keep updating size till all descendants are checked
  }
  return totalsize;//return the total size
}
void VFS::showbin() {//this function shows oldest member in the bin with its path
  if (bin.isEmpty())//if the bin is empty throw error
    throw underflow_error("Bin is empty!");
  else {
    string filetype = "dir";
    if (bin.front_element()->type == false)
      filetype = "file";
    cout << filetype << " " << bin.front_element()->name << " "<< bin.front_element()->size << " " << bin.front_element()->getTime()<< endl;//show bin grandpa node's details
    cout<<pwd(bin.front_element())<<endl;//show path
 }
}
void VFS::emptybin() {//empty the bin
  if (bin.isEmpty())
    throw underflow_error("Bin is empty!");
  else {
    while (!bin.isEmpty()) {
      Inode *killer;//create a killer node
      killer = bin.dequeue();//remove front of bin and assign to killer
      delete killer;//killer kills this element
    }
  }
}
void VFS::exit() {//when exited the data should be stored in vfs.dat
  ofstream rekas("vfs.dat", ios::app);
  if (!rekas.is_open())
    throw underflow_error("Cannot open vfs storage data.");
  write(rekas, root);
}
Inode *VFS::getNode(string path) {//this function gets node of the path by breaking the path using the  / and then storing it into a queue
  char *block = new char[path.size() + 1];
  for (long unsigned int i = 0; i < path.size(); i++) {
    block[i] = path[i];
  }
  block[path.size()] = '\0';
  char *point;
  point = strtok(block, "/");
  Queue<string> pathway(path.size());
  while (point != NULL) {
    pathway.enqueue(point);
    point = strtok(NULL, "/");
  }
  Inode *searchnode = root;
  while (!pathway.isEmpty()) {//after storing in a queue, we keep moving based on the path to the last child using recurssion and then we return the child
    searchnode = getChild(searchnode, pathway.dequeue());
  }
  return searchnode;
}
Inode *VFS::getChild(Inode *ptr, string childname) {//this gets the child of the ptr by giving it the name of the child
  Inode *scanner = ptr->children[0];
  if (!find_helper(ptr, childname) || ptr == nullptr)//if child is not there or ptr is null throw error
    throw underflow_error("Folder/file not found under this current folder!");
  for (int i = 0; scanner->getName() != childname && i < ptr->children.size();
       i++) {
    scanner = ptr->children[i];
  }
  return scanner;
}
bool VFS::find_helper(Inode *ptr, string name) {//this checks if the child exits in the first place
  if (ptr == nullptr)
    throw underflow_error("Folder/file not found under this current folder!");
  for (int i = 0; i < ptr->children.size(); i++) {
    if (ptr->children[i]->getName() == name)
      return true;
  }
  return false;
}
string VFS::getTime() {//this gets time and stores it as string
  time_t now = time(NULL);
  char *dt = ctime(&now);
  string date = dt;
  string date2 =
      date.substr(4, 3) + "-" + date.substr(8, 2) + "-" + date.substr(20, 4);
  return date2;
}
void VFS::write(ofstream &fout, Inode *ptr) {//this function writes the tree into the file
  fout << pwd(ptr) << ", " << ptr->size << ", " << ptr->cr_time << endl;
  ;
  for (int i = 0; i < ptr->children.size(); i++) {
    write(fout, ptr->children[i]);
  }
}
void VFS::lssort(Inode* point) {//this function sorts the children
  if(point==nullptr){point=curr_inode;}
  for (int i = point->children.size() - 1; i >= 0; i--) {
    for (int j = 0; j < i; j++) {
      if (point->children[j]->size < point->children[j + 1]->size) {
        point->children.swap(j, j + 1);//swap is in the vector.hpp and it receives the index of the children to be swapped
      }
    }
  }
}
void VFS::find(string name){//find finds a child
  preOrderTraversal(root,name);//go throw the whole tree
}
void VFS::preOrderTraversal(Inode* node,string name) {
if (node!=nullptr) {
  if(node->getName()==name){cout<<pwd(node)<<endl;}//if we find a math rpint its path and move on
  for (int i = 0; i < node->children.size(); i++) {
    preOrderTraversal(node->children[i],name); 
  }
}
}
void VFS::recover(){//recover recovers the oldest memeber of the bin
  if (bin.isEmpty())
    throw underflow_error("Bin is empty!");
  else {
    Inode *renew;
    renew = bin.dequeue();
    Inode* daddy=renew->parent;//it does this by using the parent and not the path queue... sorry but i thought this was faster
    daddy->children.push_back(renew);
    lssort(daddy);//sorts the children 
  }
}
void VFS::mv(string file, string folder){//moves a file or folder to another file or folder
  Inode* filecontainer=curr_inode; Inode* foldercontainer=curr_inode;//initialize the value of the contaners to the current node
  if(!ispath(folder)){//if it is not a path and file is not in currnods childlist throw error
    if(!find_helper(foldercontainer,folder))throw underflow_error("Folder not found!");
    for (int i = 0; foldercontainer->getName() != folder && i < curr_inode->children.size(); i++) {
    foldercontainer = filecontainer->children[i];//make foldercontainer the child that has name ,match
  }}
  string filename=file;//initialise it to file
  if(ispath(file)){//if it is a path
    Inode* temp=getNode(file);//get node
    filecontainer=temp->parent;// get the container using tyhe parent
    filename=temp->getName();//get the name using getname
  }
  if(ispath(folder)){//if the folder is a path
    foldercontainer=getNode(folder);
  }
  if(!ispath(file)&&!find_helper(filecontainer,file)){throw underflow_error("File not found!");}
  if(!ispath(folder)&&!getNode(folder)->type){throw underflow_error("Can't move into file!");}
  if((ispath(file)&&foldercontainer==getNode(file))||file==folder)throw underflow_error("Cannot move file to itself!");
  Inode *scanner = filecontainer->children[0];
  int fileindex = 0;
  for (int i = 0; scanner->getName() != filename && i < filecontainer->children.size(); i++) {//find the child under the filecontainer and its index
    scanner = filecontainer->children[i];
    fileindex = i;
  }
  if (scanner->getName() == filename) {//if we find it,
    if(!foldercontainer->type)throw underflow_error("Can't move into file!");
    foldercontainer->children.push_back(scanner);//add it to the folder
    scanner->parent->children.erase(fileindex);//erase it from the old folder
    scanner->parent=foldercontainer;//make its parent the new folder
  }
}
VFS::~VFS(){
  delete root;//delete the root ... the other vector destructors will deal with the rest
}