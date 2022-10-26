#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <iostream>
#include <queue>
using namespace std;

enum Color { RED, BLACK }; // цвет

/*********************************************************/
struct Node // Узел дерева
{
    string data; // данные узла 
    Color color; // цвет (черный/красный)
    Node* left, * right, * parent; // левый и правый дети, родитель

    Node(string data) { // консруктор узла
        this->data = data; // записываем инф-ию в узел
        color = RED; // (каждый новый добавляемый узел в дерево - всегда КРАСНЫЙ)
        left = right = parent = nullptr;
    }
};
/*********************************************************/

class RBTree // класс дерева
{
private:
    Node* root; // корень 
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
