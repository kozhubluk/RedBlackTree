#include "RBTree.h"

RBTree::RBTree() { // конструктор класса
    root = nullptr;
}

int RBTree::getColor(Node*& node) { // получаем цвет узла (геттер)
    if (node == nullptr) // листья (null - узлы) окрашены в черный цвет
        return BLACK;

    return node->color;
}

void RBTree::setColor(Node*& node, Color color) { // сеттер для цвета
    if (node == nullptr)
        return;

    node->color = color;
}

Node* RBTree::insert(Node*& root, Node*& ptr) { // вставка элемента
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

void RBTree::insertValue(string n) { // вставка нового значения в дерево
    Node* node = new Node(n);
    root = insert(root, node);
    balanceInsert(node);
}

void RBTree::rotateLeft(Node*& ptr) { // левый поворот 
    Node* right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr) // если правй ребенок не равен пустому указателю
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

void RBTree::rotateRight(Node*& ptr) { // правый поворот
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
    Node* parent = nullptr; // родитель (отец) 
    Node* grandparent = nullptr; // дед
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) { // нарушение вида: отец - красный
        parent = ptr->parent; // получаем указатель на отца
        grandparent = parent->parent; // получаем указатель на деда 
        if (parent == grandparent->left) { // если отец слева от деда 
            Node* uncle = grandparent->right; // то дядя справа от деда
            if (getColor(uncle) == RED) { // если дядя тоже красный 
                // инвертируем отца, дядю и деда 
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            }
            else { // если дядя черный 
                if (ptr == parent->right) { // если текущий узел справа от отца
                    rotateLeft(parent); // левый поворот 
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color); // инвертируем отца и деда 
                ptr = parent;
            }
        }
        else { // если отец справа от деда, то дядя слева от деда
            Node* uncle = grandparent->left;
            // всех инверируем 
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            }
            else {
                if (ptr == parent->left) { // если узел слева от родителя 
                    rotateRight(parent); // правый поворот 
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color); // инвертируем отца и деда
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK); // корень черный 
}

/*********************************************************************/
void RBTree::inorder(Node*& ptr) { // симметричный обход дерева
    if (ptr == nullptr) // если дерево пустое
        return;

    inorder(ptr->left); // левый потомок
    cout << ptr->data << " ";
    (ptr->color == BLACK) ? cout << " black\n" : cout << " red\n";
    inorder(ptr->right); // правй потомок 
}

void RBTree::inorder() {
    inorder(root);
}
/*********************************************************************/


/************************** сумма значений листьев ******************************/
void RBTree::summa(Node*& ptr) {
    if (ptr == nullptr) // если дерево пустое
        return;
    if (ptr->left == nullptr && ptr->right == nullptr) sum += ptr->data + " ";
    summa(ptr->left); // левый потомок
    summa(ptr->right); // правй потомок 
}

string RBTree::summa() {
    this->sum = "";
    summa(root);
    return sum;
}
/******************************************************************************/


/***************************ВЫСОТА ДЕРЕВА*******************************/
int RBTree::heigh() {
    return heigh(this->root);
}
int RBTree::heigh(Node*& ptr)
{
    if (ptr == nullptr) {
        return 0;
    }
    else if (ptr->left == nullptr && ptr->right == nullptr) { // возвращаем 0 если нет дочерних эелементов
        return 0;
    }
    else if (heigh(ptr->left) > heigh(ptr->right)) // выбираем макс длину
        return heigh(ptr->left) + 1;
    else
        return heigh(ptr->right) + 1;
}
/*********************************************************************/


// обход в ширину 
void RBTree::breadthFirst() {
    if (root == nullptr) // если дерево пустое
        return;

    queue <Node*> q;
    //Для начала поместим в очередь корень
    q.push(this->root);

    while (q.size() != 0) {
        Node* tmp;
        tmp = q.front();
        q.pop(); // удаляем первый элемент очереди
        cout << tmp->data;
        (tmp->color == BLACK) ? cout << " black\n" : cout << " red\n"; // выводим информацию о первом элементе очереди
        //Если есть левый наследник, то помещаем его в очередь для дальнейшей обработки
        if (tmp->left) {
            q.push(tmp->left);
        }
        //Если есть правый наследник, то помещаем его в очередь для дальнейшей обработки
        if (tmp->right) {
            q.push(tmp->right);
        }
    }
}

void RBTree::print() { // вывод 
    if (root == nullptr) // проверяяем корень
        cout << "empty RBtree\n";
    else
        print(root);
}
void RBTree::print(Node* node) { // вывод
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
