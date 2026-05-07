// Дан список целых чисел. 
// Построить дерево бинарного поиска.
// Найти средний по значению лист и удалить его "деда".
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

struct tree // Структура узла дерева
{
    int inf;
    tree* right;
    tree* left;
    tree* parent;
};

tree *node(int x){ // Создание нового узла
    tree *n = new tree;
    n->inf = x;
    n->left = n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree *&tr, int x){ // Вставка элемента
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
            }
        }
    }
}

void collect_leaves(tree *tr, vector<tree*> &leaves){ // Сбор всех листьев дерева
    if (!tr) {
        return;
    }
    if (!tr->left && !tr->right){
        leaves.push_back(tr);
        return;
    }
    collect_leaves(tr->left, leaves);
    collect_leaves(tr->right, leaves);
}

tree *find_node(tree *tr, int x){ // Поиск узла по значению
    if (!tr || tr->inf == x){
        return tr;
    }
    if (x < tr->inf){
        return find_node(tr->left, x);
    }
    return find_node(tr->right, x);
}

tree *find_min(tree *tr){ // Поиск минимального элемента
    if (!tr){
        return NULL;
    }
    while (tr->left){
        tr = tr->left;
    }
    return tr;
}

void delete_node(tree *&root, tree *v){ // Удаление узла из дерева
    if (!v){
        return;
    }
    tree *p = v->parent;

    if (!v->left && !v->right){
        if (p){
            if (p->left == v){
                p->left = NULL;
            } else {
                p->right = NULL;
            }
        } else {
            root = NULL;
        }
        delete v;
        return;
    }

    if (!v->left || !v->right){
        tree *child = v->left ? v->left : v->right;
        if (p){
            if (p->left == v){
                p->left = child;
            } else {
                p->right = child;
            }
        } else {
            root = child;
        }
        child->parent = p;
        delete v;
        return;
    }

    tree *succ = find_min(v->right);
    v->inf = succ->inf;
    delete_node(root, succ);
}

void inorder(tree *tr){ // Симметричный обход
    if (tr){
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

int main(){
    int n;
    cout << "Введите кол-во чисел: ";
    cin >> n;

    tree *tr = NULL;
    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        insert(tr, num);
    }

    vector<tree*> leaves;
    collect_leaves(tr, leaves);

    if (leaves.empty()) {
        cout << "В дереве нет листьев.";
        return 0;
    }

    vector<int> leaf_values;
    for (tree *leaf : leaves)
        leaf_values.push_back(leaf->inf);
    sort(leaf_values.begin(), leaf_values.end());
    int median_val = leaf_values[leaf_values.size() / 2];

    tree *median_leaf = find_node(tr, median_val);
    if (!median_leaf || median_leaf->left || median_leaf->right) {
        return 0; // не является листом.
    }

    tree *parent = median_leaf->parent;
    if (!parent || !parent->parent) {
        return 0; // нет деда
    }
    tree *granddad = parent->parent;

    cout << "Средний лист: " << median_val << endl;

    delete_node(tr, granddad);

    cout << "Дерево после удаления:" << endl;
    inorder(tr);
    cout << endl;

    return 0;
}