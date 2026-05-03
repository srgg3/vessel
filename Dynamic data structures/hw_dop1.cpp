// Дано математическое выражение. Вывести его в префиксной форме

#include <iostream>
#include <string>

using namespace std;

struct node
{
    char inf;
    node *next;
};

void push(node *&h, char x){
    node *r = new node;
    r->inf = x;
    r->next = h;
    h = r;
}

char pop(node *&h){
    char x = h->inf;
    node *r = h;
    h = h->next;
    delete r;
    return x;
}

void reverse(node *&h){
    node *h1 = NULL;
    while (h){
        push(h1, pop(h));
    }
    h = h1;
}

int prior(char op){
    if (op == '+' or op == '-'){
        return 1;
    }
    if (op == '*' or op == '/'){
        return 2;
    }
    return 0;
}

string pref(const string &s){
    node *op = NULL;
    string output;

    for (int i = s.length() - 1; i >= 0; --i){
        char ch = s[i];

        if (isalnum(ch)){
            output += ch;
        } else if (ch == ')'){
            push(op, ch);
        } else if (ch == '('){
            while (op and op->inf != ')'){
                output += pop(op);
            }
            if (op and op->inf == ')'){
                pop(op);
            }
        } else if (ch == '+' or ch == '-' or ch == '*' or ch == '/'){
            while (op and op->inf != ')' and prior(op->inf) > prior(ch)){
                output += pop(op);
            }
            push(op, ch);
        }
    }

    while (op){
        output += pop(op);
    }

    node *tmp = NULL;
    for (char c : output){
        push(tmp, c);
    }
    string ans;
    while (tmp){
        ans += pop(tmp);
    }
    return ans;
}

int main(){
    string s;
    cout << "Выражение: ";
    getline(cin, s);

    string ans = pref(s);
    cout << "Ответ: " << ans << endl;

    return 0;
}