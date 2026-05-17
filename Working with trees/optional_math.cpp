// Дополнительное задание (факультатив). Деревья
// Дано математическое выражение. Построить на его основе дерево по примеру, приведенному в лекциях.
// Вывести данное выражение в префиксной и постфиксной формах, используя соответствующие обходы.

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct tree {
    char inf;
    tree* left;
    tree* right;
    tree* parent;
};

tree* node(char x){
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}

tree* create_tree(const string& str){
    tree* tr = NULL;
    for (size_t i = 0; i < str.length(); i++){
        char ch = str[i];
        tree* n = node(ch);

        if (isdigit(ch)){
            if (!tr){
                tr = n;
            } else {
                tree* y = tr;
                while (y->right){
                    y = y->right;
                }
                n->parent = y;
                y->right = n;
            }
        }
        else if (ch == '*' || ch == '/'){
            if (tr && isdigit(tr->inf)){
                tr->parent = n;
                n->left = tr;
                tr = n;
            } else {
                n->parent = tr;
                n->left = tr->right;
                if (tr->right)
                    tr->right->parent = n;
                tr->right = n;
            }
        }
        else if (ch == '+' || ch == '-'){
            if (tr){
                tr->parent = n;
                n->left = tr;
            }
            tr = n;
        }
    }
    return tr;
}

void pre_order(tree* tr){
    if (tr){
        cout << tr->inf;
        pre_order(tr->left);
        pre_order(tr->right);
    }
}

void post_order(tree* tr){
    if (tr){
        post_order(tr->left);
        post_order(tr->right);
        cout << tr->inf;
    }
}

int main(){
    string expr;
    cout << "Введите мат. выражение: ";
    getline(cin, expr);

    string clean;
    for (char c : expr)
        if (!isspace(c)) clean += c;
    expr = clean;

    tree* root = create_tree(expr);

    cout << "Префиксная форма: ";
    pre_order(root);
    cout << endl;

    cout << "Постфиксная форма: ";
    post_order(root);
    cout << endl;
    return 0;
}