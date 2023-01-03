// mymap.h
//
//Project 5 – mymap
//CS 251, Fall 2022
//
//In this program we made a my map class in which we have functions in whic we can add values and then we can store 
//them respectifully and then output them when needed.
//
//
//Name: Imran Khan
//UIN: 654046372
//Using vscode windows
//
//Resources used:
//Program 4-Imran Khan
#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

   /*In this function we take in the root as the parameter and then we copy it to another tree and this funstion is used in copying the tree
   to another tree. We copy over the key value and the value to the new tree*/
    void _anotherTree(NODE* root2)
    {
        
      if(root2 != nullptr){
        //using the put funtion we made
        this->put(root2->key, root2->value);//inserts thre value in the new binary tree
        _anotherTree(root2->left);
      //checking for threading
        if(root2-> isThreaded == false){
          _anotherTree(root2->right);
        }
         
      }
        
    }//end of _anotherTree

    /*In this function we delete the following tree as the root is in the parameter and then we run though the whoole tree and then we delete each
    occuring node with it and then we relase the memory associated with it so we clear up the memory and so there are no leaks*/
    void _deleteTree(NODE *curr) {
    
    // check if the tree is empty
      if (curr == nullptr) {
        return;
      }
      
      
      _deleteTree(curr->left);//delete the left hand side of the tree
      
      if(curr ->isThreaded == false){
       _deleteTree(curr->right);//delete the right hand side of the tree
      }
      

      size--;
      delete curr;
      
    }//end of _deleteTree

   /*In this fucntion we check if the value is in the tree and then we return the bool x which contains the boolean type if the value is found inside the tree or if itr is not found we use traveral
   for this mehtod to check if it is inside it*/
    void _traverseContains(NODE* cur,keyType key, bool &x)
    {
      //if the treee is empty
      if(cur == nullptr){
        return;
      }
      else{
          
        _traverseContains(cur->left,key,x);//goes through the function again
          
          
          
        if(key == cur->key){
          x =  true;
            
        }

        _traverseContains(cur->right,key,x);//goes through the function again
      }
        
    }//end of _traverseContains

    /*In this function we get the following value that we are lookinjg for and then we return that value if needed and if it is foundd inside the function we have both the key and the value inside the parameter
    so wehn we find it we return the value to the given function*/
    void _traverseGet(NODE* cur,keyType key, valueType &x)
    {
      //if tree is empty
      if(cur == nullptr){
        return;
      }
      else{
          
        _traverseGet(cur->left,key,x);//goes through the function again
          
          
          
        if(key == cur->key){
          x = cur->value;
            
        }

        _traverseGet(cur->right,key,x);//goes through the function again
      }
        
    }//end of _traverseGet


   /*In this function  we use the operator function and set the operator and see if both the trees are the same or not*/
    void _traverseOperator(NODE* cur, keyType key, valueType &value,bool &x)
    {
      //if tree is empty
      if(cur == nullptr){
          return;
        }
        else{
      
          _traverseOperator(cur->left,key,value,x);//goes through the function again
          
          
        
            if (key == cur->key){
              x = true;
              value = cur -> value;
            }
            
            
          
          
          _traverseOperator(cur->right,key,value,x);//goes through the function again
        }
        
    }//end of _traverseOperator

    /*In this function we go though the whole tree and then we use this function to help the toString fucntion and we take out the output which contains the list
    of what is inside the treee*/
    void _traverseString(NODE* cur,ostream &output)
    {
      //if tree is empty
      if(cur == nullptr){
          return;
        }
        else{
          
          _traverseString(cur->left,output);//goes through the function again
          
            output<<cur-> key;
            output<<" value: ";
            output<<cur-> value<<endl;
          
          _traverseString(cur->right,output);//goes through the function again
        }
    }//end of _traverseString

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        //This procedure should move curr on to the subsequent node in the sequence.
        //O(logN)
        iterator operator++() {

          //checks if the tree is threaded or not
          if(curr-> isThreaded){
            curr = curr->right;
          }
          else{
            curr = curr->right;
            while(curr->left != nullptr ){
            curr = curr->left;
            }
          }
       

          return iterator(curr);  // returns the next node inside the tree
        }
    };

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {

      size =0 ;
      root = nullptr;

    }

    //
    // copy constructor:
    //
    /*creates a duplicate of the "other" mymap in a new mymap.
    adjusts the member variables for each one.
    O(nlogn) computation time, where n represents the total number of threaded, self-balancing BST nodes.*/
    mymap(const mymap& other) {
      root = nullptr;
      size = 0;
      _anotherTree(other.root);
    }

    //
    // operator=:
    //
   /*creates a duplicate of the "other" mymap after clearing "this" mymap.
    adjusts the member variables for each one.
    O(nlogn) time complexity, where n is the total number of threaded, self-balancing BST nodes.*/
    mymap& operator=(const mymap& other) {

      this->clear();
        
      _anotherTree(other.root);//makes the other tree
 
      return *this;
    }

    // clear:
    //
   /*releases the RAM connected to the mymap; testing is possible.
    O(n), where n is the total number of threaded, self-balancing BST nodes, is the time complexity.*/
    void clear() {

      _deleteTree(root);
      
      root = nullptr;
    }

    //
    // destructor:
    //
    /*releases the memory corresponding to the mymap.
    O(n), where n is the total number of threaded nodes, is the time complexity.
    BST that self-balances.*/
    ~mymap() {
      
        clear();

    }

    //
    // put:
    //
    /*based on the key, inserts the key/value into the threaded, self-balancing BST.
    Time complexity: O(logn + mlogm), where m is the number of nodes in the sub-tree that has to be rebalanced and n is the total number of nodes in the threaded, self-balancing BST.
    Complexity of space: O (1)*/
    void put(keyType key, valueType value) {


      if(this-> root == nullptr){

        //makes new nodes on the tree accordingly
        NODE * temp = new NODE;
        temp->key = key;
        temp->left =NULL;
        temp->right =NULL;
        temp->isThreaded =false;
        temp->value=value;

        size++;
        root = temp;
        
        
      }
      else{

        //makes another node and makes it a default value
        NODE *temp = root;
        NODE *prev = nullptr;
       
        

        while(temp != nullptr){

          if(key == temp->key){
       
          
            //if they are the same then change the vlaue of the node in that position
            // do not increase the size
            temp->value = value;
            
            return;
            
          
          }
          if(key < temp->key){
            //moves to the left because the value is lower that the parent in the binary tree
            prev = temp;
            temp = temp->left;
          }
          else{
            //moves to the right is not then
            prev = temp;
      
            if(temp -> isThreaded){
              temp = nullptr;
            }
            else{
              temp = temp->right;
            }
          }

        }


        if(key < prev->key){
          //moves to the left because the value is lower that the parent in the binary tree
          //adds the value to the left side
          NODE *add = new NODE;
          add->key = key;
          add->left =nullptr;
          add->right =nullptr;
          add->isThreaded =false;
          add->value = value;

          add->isThreaded = true;
          prev->left = add; 
          add->right = prev; 
          size++;

        }

        else if(key > prev->key){
          //moves to the right because the value is lower that the parent in the binary tree
          //adds the value to the right side
          NODE *add = new NODE;
          add->key = key;
          add->left =nullptr;
          add->right =nullptr;
          add->isThreaded =false;
          add->value = value;

          add->isThreaded =true;
          prev->isThreaded =false;
          add->right = prev -> right;
          prev->right = add; 
          size++;
        }
        
        
      }
    } 

    //
    // contains:
    /*if the key is present in mymap, returns true; otherwise, returns false.
    O(logn), where n is the total number of nodes in the threaded, self-balancing BST, is the time complexity*/
    bool contains(keyType key) {
      NODE* head = root;
        
      bool x = false;
      _traverseContains(head,key, x);  
      return x;//checks if it contains it
    }

    //
    // get:
    //
    /*returns the value associated with the specified key; if the key cannot be found, valueType() is returned by default (but not added to mymap).
    Temporal complexity O(logn) for the threaded, self-balancing BST, where n is the total number of nodes*/
    valueType get(keyType key) {

      NODE* head = root;
      if(root == nullptr){
         return 0;
      }
        
      valueType x;
      _traverseGet(head,key, x);  
   
      return x;

    }

    //
    // operator[]:
    //
    /*returns the value associated with the specified key; in the absence of a key, valueType() is returned by default (and a new key/value pair is created and added to the map as a consequence).
    Temporal complexity O(logn + mlogm), where n denotes the total number of threaded, self-balancing BST nodes and m denotes the total number of sub-tree nodes that require rebalancing.
    Complexity of space: O (1)*/
    valueType operator[](keyType key) {
      bool x = false;
      valueType value;
      _traverseOperator(root,key,value,x);
      if(x == false){
        put(key,valueType());
        return valueType();
      }
      else{
        return value;
      }
    }

    //
    // Size:
    //
    /*returns 0 if the mymap is empty and the number of key/value pairs.
    O(1)*/
    int Size() {
      return size;  
    }

    //
    // begin:
    //
   /*provides an iterator to the first NODE in the list.
    O(logn), where n is the total number of nodes in the threaded, self-balancing BST, is the time complexity*/  
    iterator begin() {

      NODE* curr = nullptr;
      curr = root;
      if(curr == nullptr){

       }
      else{
      
      while(curr->left != nullptr ){
        curr = curr->left;
      }

      cout<<curr->value<<endl;
      }


      return iterator(curr);  
    }

    //
    // end:
    //
    /*yields an iterator to the NODE that is last in the list.
    You have been granted this responsibility. Time Complexity: O(1)*/
    iterator end() {
        return iterator(nullptr);
    }

    //
    // toString:
    //
    /*provides an orderly string containing the whole contents of the mymap.
    "key: 8 value: 80; key: 15 value: 150; key: 20 value: 200" is the format for the numbers 8/80, 15/150, and 20/200.
    O(n), where n is the total number of nodes in the threaded, self-balancing system, is the time complexity. BST*/     
    string toString() {
      NODE *curr = nullptr;
      stringstream output;
      if(root == nullptr){
          output<<"Empty";
        }
      else{

        curr = root;
        while(curr->left != nullptr ){
          curr = curr->left;
        }
        while(curr != nullptr){
          output<<" key: ";
          output<<curr-> key;
          output<<" value: ";
          output<<curr-> value<<endl;
          //checks if it is threaded
          if(curr -> isThreaded)
          {
            curr = curr -> right;
          }
          else
          {
            curr = curr -> right;
            while(curr->left != nullptr )
            {
              curr = curr->left;
            }
          }
          
        }
      }


        return output.str();  // returns the output in an string format
    }

    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST 
    //

    
    vector<pair<keyType, valueType> > toVector() {


        // TODO: write this function.


        return {};  // TODO: Update this return.
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string checkBalance() {


        // TODO: write this function.


        return {};  // TODO: Update this return.
    }
};