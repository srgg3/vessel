// Создать стек, содержащий буквы латинского алфавита. 
// В новый стек после первой гласной буквы (первой, введенной из файла, или с клавиатуры) 
// вставить вопросительный знак. Порядок следования букв в новом стеке должен совпадать с первоначальным. 
// Например, было q, w, e, r, t, u, i, o, p, s, d, a.  Cтало q, w, e, ?, r, t, u, i, o, p, s, d, a.  

#include <iostream>
#include <string>

using namespace std;

struct node {
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

bool it_is_glas(char x){
    return x == 'e' or x == 'a' or x == 'u' or x == 'i' or x == 'o' or x == 'y' 
        or x == 'E' or x == 'A' or x == 'U' or x == 'I' or x == 'O' or x == 'Y';
}

int main(){
    node *head = NULL;
    cout << "Введите строку: ";
    string s = "";
    getline(cin, s);

    for (char c : s)
        push(head, c);

    reverse(head);

    node *res = NULL;
    bool paste = false;

    while (head){
        char x = pop(head);
        push(res, x);

        if (!paste and it_is_glas(x)){
            push(res, '?');
            paste = true;
        }
    }

    reverse(res);

    while (res){
        cout << pop(res) << " ";
    }

    return 0;
}