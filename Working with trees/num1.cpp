// Дан список целых чисел. Построить дерево бинарного поиска. Дан узел Х. 
// Если он существует в дереве, найти его глубину.
// Пример:
// Введите кол-во чисел: 7
// Введите элементы: 8 3 10 1 6 16 4
// Введите узел Х = 4
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

int find_depth(tree *tr, int x, int cnt = 0){
    if (!tr){
        return 0;
    }
    if (tr->inf == x){
        return cnt;
    }
    int left = find_depth(tr->left, x, cnt + 1);

    if (left != -1){
        return left;
    }

    return find_depth(tr->right, x, cnt + 1);
}

int main(){
    int n = 0;
    cout << "Введите кол-во чисел: ";
    cin >> n;

    cout << "Введите элементы: ";

    tree *tr = NULL;
    for (int i = 0; i < n; i++){
        int num = 0;
        cin >> num;
        insert(tr, num);
    }

    int x = 0;
    cout << "Введите узел Х = ";
    cin >> x;

    int cnt = find_depth(tr, x);
    if (cnt != 0){
        cout << "Узел найден" << endl;
        cout << "Глубина узла: " << cnt << endl;
    } else {
        cout << "Узел не найден" << endl;
    }
}