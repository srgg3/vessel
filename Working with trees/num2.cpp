// Дан список целых чисел. Построить дерево бинарного поиска. 
// Вывести все четные листья. Если таких нет, вывести сообщение об этом.
// Пример:
// Введите кол-во чисел: 7
// Введите элементы: 8 3 10 1 6 16 4
//       8
//    3    10
//  1    6    16
//      4 

#include <iostream>
#include <stack>

using namespace std;

struct tree
{
    int inf;
    tree* right;
    tree* left;
    tree* parent;
};

tree *node(int x){
    tree *n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree *&tr, int x){
    tree *n = node(x);
    if (!tr){
        tr = n;
    } else {
        tree *y = tr;
        while (y){
            if (n->inf > y->inf){
                if (y->right){
                    y = y->right;
                } else {
                    n->parent = y;
                    y->right = n;
                    break;
                }
            } else if (n->inf < y->inf){
                if (y->left){
                    y = y->left;
                } else {
                    n->parent = y;
                    y->left = n;
                    break;
                }
            } else {
                break;
            }
        }
    }
}


void print_even_leaves(tree *tr, bool &found){
    if (!tr){
        return;
    }

    if (!tr->left && !tr->right){
        if (tr->inf % 2 == 0){
            cout << tr->inf << " ";
            found = true;
        }
        return;
    }
    print_even_leaves(tr->left, found);
    print_even_leaves(tr->right, found);
}

int main(){
    int n;
    cout << "Введите кол-во чисел: ";
    cin >> n;

    tree *tr = NULL;
    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++){
        int num;
        cin >> num;
        insert(tr, num);
    }

    bool found = false;
    cout << "Чётные листья: ";
    print_even_leaves(tr, found);

    if (!found){
        cout << "Нет чётных листьев";
    }
    return 0;
}