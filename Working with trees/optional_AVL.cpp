// Работа с AVL деревом (факультатив)
// Выполнить любую из задач задания, используя AVL дерево
// Необходимо создать дерево в соответствии с заданием, вывести его элементы,
// используя симметричный обход и выполнив задание, вывести новое дерево.
// 2. Дано дерево. Удалить элементы, кратные 𝑋.

#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) : key(k), height(1), left(NULL), right(NULL) {}
};

int get_height(Node* n) {
    if (n == NULL) {
        return 0;
    } else {
        return n->height;
    }
}

int balance_factor(Node* n) {
    if (n == NULL) {
        return 0;
    } else {
        return get_height(n->left) - get_height(n->right);
    }
}

void update_height(Node* n) {
    if (n != NULL) {
        n->height = 1 + max(get_height(n->left), get_height(n->right));
    }
}

Node* rotate_right(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    update_height(y);
    update_height(x);
    return x;
}

Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    update_height(x);
    update_height(y);
    return y;
}

Node* balance_node(Node* n) {
    if (n == NULL) return n;
    update_height(n);
    int bf = balance_factor(n);
    if (bf > 1) {
        if (balance_factor(n->left) < 0)
            n->left = rotate_left(n->left);
        return rotate_right(n);
    }
    if (bf < -1) {
        if (balance_factor(n->right) > 0)
            n->right = rotate_right(n->right);
        return rotate_left(n);
    }
    return n;
}

Node* insert_node(Node* root, int key) {
    if (root == NULL)
        return new Node(key);
    if (key < root->key)
        root->left = insert_node(root->left, key);
    else if (key > root->key)
        root->right = insert_node(root->right, key);
    else
        return root;
    return balance_node(root);
}

Node* min_value_node(Node* n) {
    Node* current = n;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* delete_node(Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = delete_node(root->left, key);
    else if (key > root->key)
        root->right = delete_node(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = min_value_node(root->right);
            root->key = temp->key;
            root->right = delete_node(root->right, temp->key);
        }
    }
    if (root == NULL)
        return root;
    return balance_node(root);
}

void inorder_traversal(Node* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        cout << root->key << " ";
        inorder_traversal(root->right);
    }
}

void delete_multiples(Node*& root, int X) {
    if (root == NULL) return;
    delete_multiples(root->left, X);
    delete_multiples(root->right, X);
    if (root->key % X == 0) {
        root = delete_node(root, root->key);
        delete_multiples(root, X);
    }
}

void delete_tree(Node* root) {
    if (root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

int main() {
    Node* tree = NULL;
    int n, x, X;

    cout << "Введите количество чисел: ";
    cin >> n;
    cout << "Введите элементы: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        tree = insert_node(tree, x);
    }

    cout << "Симметричный обход: ";
    inorder_traversal(tree);
    cout << endl;

    cout << "Введите X: ";
    cin >> X;

    delete_multiples(tree, X);

    cout << "Новое дерево (симметричный обход): ";
    inorder_traversal(tree);
    cout << endl;

    delete_tree(tree);
    return 0;
}