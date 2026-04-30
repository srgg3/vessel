// Создать очередь из целых чисел. 
// Выполнить циклический сдвиг очереди так, чтобы на первом месте было первое простое число. 
// Например, было  4 8 6 9 1 2 3 4 5 7. Стало 2 3 4 5 7 4 8 6 9 1

#include <iostream>
#include <string>

using namespace std;

struct node {
    int inf;
    node *next;
};

void push(node *&h, int x){
    node *r = new node;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(node *&h){
    int x = h->inf;
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

bool prost(int x){
    if (x < 2){
        return false;
    }
    for (int i = 2; i * i <= x; i++){
        if (x % i == 0){
            return false;
        }
    }
    return true;
}

int main(){
    cout << "Введите кол-во элементов: ";
    int n;
    cin >> n;

    node *st = NULL;
    cout << "Введите элементы:" << endl;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        push(st, x);
    }

    reverse(st);

    node *before = NULL;
    node *after  = NULL;
    int num = -1;
    bool found = false;

    while (st){
        int x = pop(st);
        if (!found && prost(x)){
            num = x;
            found = true;
        } else if (!found){
            push(before, x);
        } else {
            push(after, x);
        }
    }

    if (!found){
        node *res = NULL;
        while (before){
            push(res, pop(before));
        }
        reverse(res);
        while (res){
            cout << pop(res) << " ";
        }
        return 0;
    }

    reverse(after);
    reverse(before);

    cout << num << " ";
    while (after){
        cout << pop(after) << " ";
    }
    while (before){
        cout << pop(before) << " ";
    }
    return 0;
}