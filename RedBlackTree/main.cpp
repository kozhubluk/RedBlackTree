#include "RBTree.h"

int main() {
    string data;
    int c;
    RBTree rbTree;
    setlocale(LC_ALL, "RU");
    cout << "1 - вставка\n";
    cout << "2 - вывод\n";
    cout << "3 - вывод высоты\n";
    cout << "4 - вывод суммы листьев\n";
    cout << "5 - обход в ширину\n";
    cout << "6 - симметричный обход\n";
    while (cin >> c) {
        switch (c)
        {
        case(1):
            cin >> data;
            rbTree.insertValue(data);
            break;
        case(2):
            rbTree.print();
            break;
        case(3):
            cout << "высота дерева: " << rbTree.heigh() << endl;
            break;
        case(4):
            cout << "сумма листьев: " << rbTree.summa() << endl;
            break;
        case(5):
            rbTree.breadthFirst();
            break;
        case(6):
            rbTree.inorder();
            break;
        default:
            cout << "Неизвестная команда";
            break;
        }
    }
    return 0;
}
