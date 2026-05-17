// Работа с красно-черным деревом (факультатив)
// Написать функции для создания дерева, удаления элемента, вставки нового элемента, симметричного обхода.
// Необходимо создать дерево в соответствии с заданием, вывести его элементы,
// используя симметричный обход и выполнив задание, вывести новое дерево.
// 1. Дано дерево. Подсчитать сумму листьев.
// Введите количество чисел: 7
// Введите элементы: 8 3 10 1 6 16 4
// ВЫВОД:
// Симметричный обход: 1 3 4 6 8 10 16 
// Сумма листьев: 21
// Дерево (симметричный обход): 1 3 4 6 8 10 16 

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum Color {
    black, red
};

struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;

    Node(int k) : key(k), color(red), left(NULL), right(NULL), parent(NULL) {}
};

Node* grandparent(Node* x) {
    if (x != NULL && x->parent != NULL)
        return x->parent->parent;
    return NULL;
}

Node* uncle(Node* x) {
    Node* g = grandparent(x);
    if (g == NULL) return NULL;
    if (x->parent == g->left)
        return g->right;
    else
        return g->left;
}

Node* sibling(Node* x) {
    if (x == NULL || x->parent == NULL) return NULL;
    if (x == x->parent->left)
        return x->parent->right;
    else
        return x->parent->left;
}

void rotate_left(Node*& root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotate_right(Node*& root, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
}

void insert_case1(Node*& root, Node* x);
void insert_case2(Node*& root, Node* x);
void insert_case3(Node*& root, Node* x);
void insert_case4(Node*& root, Node* x);
void insert_case5(Node*& root, Node* x);

void insert_case1(Node*& root, Node* x) {
    if (x->parent == NULL) {
        x->color = black;
        root = x;
    } else {
        insert_case2(root, x);
    }
}

void insert_case2(Node*& root, Node* x) {
    if (x->parent->color == black) {
        return;
    } else {
        insert_case3(root, x);
    }
}

void insert_case3(Node*& root, Node* x) {
    Node* u = uncle(x);
    Node* g = grandparent(x);
    if (u != NULL && u->color == red) {
        x->parent->color = black;
        u->color = black;
        g->color = red;
        insert_case1(root, g);
    } else {
        insert_case4(root, x);
    }
}

void insert_case4(Node*& root, Node* x) {
    Node* g = grandparent(x);
    if (x == x->parent->right && x->parent == g->left) {
        rotate_left(root, x->parent);
        x = x->left;
    } else if (x == x->parent->left && x->parent == g->right) {
        rotate_right(root, x->parent);
        x = x->right;
    }
    insert_case5(root, x);
}

void insert_case5(Node*& root, Node* x) {
    Node* g = grandparent(x);
    x->parent->color = black;
    g->color = red;
    if (x == x->parent->left)
        rotate_right(root, g);
    else
        rotate_left(root, g);
}

void rb_insert(Node*& root, int key) {
    if (root == NULL) {
        root = new Node(key);
        root->color = black;
        return;
    }

    Node* y = NULL;
    Node* x = root;
    while (x != NULL) {
        y = x;
        if (key < x->key)
            x = x->left;
        else if (key > x->key)
            x = x->right;
        else
            return;
    }

    Node* newNode = new Node(key);
    newNode->parent = y;
    if (key < y->key)
        y->left = newNode;
    else
        y->right = newNode;

    insert_case1(root, newNode);
}

void rb_replace(Node*& root, Node* u, Node* v) {
    if (u->parent == NULL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

Node* tree_minimum(Node* x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

void delete_case1(Node*& root, Node* x);
void delete_case2(Node*& root, Node* x);
void delete_case3(Node*& root, Node* x);
void delete_case4(Node*& root, Node* x);
void delete_case5(Node*& root, Node* x);
void delete_case6(Node*& root, Node* x);

void delete_case1(Node*& root, Node* x) {
    if (x->parent == NULL) {
        return;
    } else {
        delete_case2(root, x);
    }
}

void delete_case2(Node*& root, Node* x) {
    Node* s = sibling(x);
    if (s != NULL && s->color == red) {
        x->parent->color = red;
        s->color = black;
        if (x == x->parent->left)
            rotate_left(root, x->parent);
        else
            rotate_right(root, x->parent);
    }
    delete_case3(root, x);
}

void delete_case3(Node*& root, Node* x) {
    Node* s = sibling(x);
    if (x->parent->color == black &&
        (s == NULL || s->color == black) &&
        (s == NULL || s->left == NULL || s->left->color == black) &&
        (s == NULL || s->right == NULL || s->right->color == black)) {
        if (s != NULL)
            s->color = red;
        delete_case1(root, x->parent);
    } else {
        delete_case4(root, x);
    }
}

void delete_case4(Node*& root, Node* x) {
    Node* s = sibling(x);
    if (x->parent->color == red &&
        (s == NULL || s->color == black) &&
        (s == NULL || s->left == NULL || s->left->color == black) &&
        (s == NULL || s->right == NULL || s->right->color == black)) {
        if (s != NULL)
            s->color = red;
        x->parent->color = black;
    } else {
        delete_case5(root, x);
    }
}

void delete_case5(Node*& root, Node* x) {
    Node* s = sibling(x);
    if (s != NULL && s->color == black) {
        if (x == x->parent->left &&
            (s->right == NULL || s->right->color == black) &&
            (s->left != NULL && s->left->color == red)) {
            s->color = red;
            s->left->color = black;
            rotate_right(root, s);
        } else if (x == x->parent->right &&
                   (s->left == NULL || s->left->color == black) &&
                   (s->right != NULL && s->right->color == red)) {
            s->color = red;
            s->right->color = black;
            rotate_left(root, s);
        }
    }
    delete_case6(root, x);
}

void delete_case6(Node*& root, Node* x) {
    Node* s = sibling(x);
    if (s != NULL) {
        s->color = x->parent->color;
        x->parent->color = black;
        if (x == x->parent->left) {
            if (s->right != NULL)
                s->right->color = black;
            rotate_left(root, x->parent);
        } else {
            if (s->left != NULL)
                s->left->color = black;
            rotate_right(root, x->parent);
        }
    }
}

bool rb_delete(Node*& root, int key) {
    Node* z = root;
    while (z != NULL) {
        if (key < z->key)
            z = z->left;
        else if (key > z->key)
            z = z->right;
        else
            break;
    }
    if (z == NULL) return false;

    Node* y = z;
    Node* x = NULL;
    Color y_original_color = y->color;

    if (z->left == NULL) {
        x = z->right;
        rb_replace(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        rb_replace(root, z, z->left);
    } else {
        y = tree_minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        } else {
            rb_replace(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_replace(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;

    if (y_original_color == black) {
        if (x != NULL && x->color == red)
            x->color = black;
        else if (x != NULL)
            delete_case1(root, x);
    }
    return true;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int leaf_sum(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL)
        return root->key;
    return leaf_sum(root->left) + leaf_sum(root->right);
}

void delete_tree(Node* root) {
    if (root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

int main() {
    Node* tree = NULL;
    int n, x;

    cout << "Введите количество чисел: ";
    cin >> n;
    cout << "Введите элементы: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        rb_insert(tree, x);
    }

    cout << "Симметричный обход: ";
    inorder(tree);
    cout << endl;

    int sum = leaf_sum(tree);
    cout << "Сумма листьев: " << sum << endl;

    cout << "Дерево (симметричный обход): ";
    inorder(tree);
    cout << endl;

    delete_tree(tree);
    return 0;
}