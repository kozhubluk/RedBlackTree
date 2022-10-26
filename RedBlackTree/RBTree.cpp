#include "RBTree.h"

RBTree::RBTree() {
    root = nullptr;
}

int RBTree::getColor(Node*& node) {
    if (node == nullptr) 
        return BLACK;

    return node->color;
}

void RBTree::setColor(Node*& node, Color color) {
    if (node == nullptr)
        return;

    node->color = color;
}

Node* RBTree::insert(Node*& root, Node*& ptr) { 
    if (root == nullptr)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insert(root->left, ptr);
        root->left->parent = root;
    }
    else if (ptr->data > root->data) {
        root->right = insert(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void RBTree::insertValue(string n) { 
    Node* node = new Node(n);
    root = insert(root, node);
    balanceInsert(node);
}

void RBTree::rotateLeft(Node*& ptr) { 
    Node* right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr) 
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RBTree::rotateRight(Node*& ptr) { 
    Node* left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RBTree::balanceInsert(Node*& ptr) {
    Node* parent = nullptr; 
    Node* grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) { 
        parent = ptr->parent; 
        grandparent = parent->parent; 
        if (parent == grandparent->left) { 
            Node* uncle = grandparent->right; 
            if (getColor(uncle) == RED) { 
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            }
            else { 
                if (ptr == parent->right) { 
                    rotateLeft(parent); 
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color); 
                ptr = parent;
            }
        }
        else { 
            Node* uncle = grandparent->left; 
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            }
            else {
                if (ptr == parent->left) { 
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color); 
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK); // êîðåíü ÷åðíûé 
}

/*********************************************************************/
void RBTree::inorder(Node*& ptr) { 
    if (ptr == nullptr) 
        return;

    inorder(ptr->left); 
    cout << ptr->data << " ";
    (ptr->color == BLACK) ? cout << " black\n" : cout << " red\n";
    inorder(ptr->right); 
}

void RBTree::inorder() {
    inorder(root);
}
/*********************************************************************/


/*******************************************************/
void RBTree::summa(Node*& ptr) {
    if (ptr == nullptr)
        return;
    if (ptr->left == nullptr && ptr->right == nullptr) sum += ptr->data + " ";
    summa(ptr->left); 
    summa(ptr->right); 
}

string RBTree::summa() {
    this->sum = "";
    summa(root);
    return sum;
}
/******************************************************************************/


/****************************************************************************/
int RBTree::heigh() {
    return heigh(this->root);
}
int RBTree::heigh(Node*& ptr)
{
    if (ptr == nullptr) {
        return 0;
    }
    else if (ptr->left == nullptr && ptr->right == nullptr) { 
        return 0;
    }
    else if (heigh(ptr->left) > heigh(ptr->right)) 
        return heigh(ptr->left) + 1;
    else
        return heigh(ptr->right) + 1;
}
/*********************************************************************/


void RBTree::breadthFirst() {
    if (root == nullptr) 
        return;

    queue <Node*> q;
    q.push(this->root);

    while (q.size() != 0) {
        Node* tmp;
        tmp = q.front();
        q.pop(); 
        cout << tmp->data;
        (tmp->color == BLACK) ? cout << " black\n" : cout << " red\n"; 
        
        if (tmp->left) {
            q.push(tmp->left);
        }
        
        if (tmp->right) {
            q.push(tmp->right);
        }
    }
}

void RBTree::print() { 
    if (root == nullptr) 
        cout << "empty RBtree\n";
    else
        print(root);
}
void RBTree::print(Node* node) {
    if (node == nullptr)
        return;
    if (node->parent == nullptr)
        cout << node->data << "(" << node->color << ") is root" << endl;
    else if (node->parent->left == node)
    {
        cout << node->data << "(" << node->color << ") is " << node->parent->data << "'s " << "left child" << endl;
    }
    else
    {
        cout << node->data << "(" << node->color << ") is " << node->parent->data << "'s " << "right child" << endl;
    }
    print(node->left);
    print(node->right);
}
