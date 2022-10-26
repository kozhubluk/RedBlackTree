#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <iostream>
#include <queue>
using namespace std;

enum Color { RED, BLACK }; 

/*********************************************************/
struct Node 
{
    string data; 
    Color color; 
    Node* left, * right, * parent; 

    Node(string data) { 
        this->data = data; 
        color = RED; 
        left = right = parent = nullptr;
    }
};
/*********************************************************/

class RBTree 
{
private:
    Node* root;
    string sum;
protected:
    void rotateLeft(Node*&);
    void rotateRight(Node*&);
    void balanceInsert(Node*&);
    int heigh(Node*&);
    void summa(Node*&);
    void inorder(Node*&);
    int getColor(Node*&);
    void print(Node* node);
    void setColor(Node*&, Color);
    Node* insert(Node*&, Node*&);
public:
    RBTree();
    void print();
    int heigh();
    string summa();
    void insertValue(string);
    void breadthFirst();
    void inorder();
};

#endif
