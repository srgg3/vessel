// Создать очередь, содержащую целые числа. 
// После всех чисел, равных максимальному числу, вставить последний нечетный элемент. 
// Например, было  2 8 2 1 6 8 8 1 2 2 8 2 1. Стало  2 8 1 2 1 6 8 1 8 1 1 2 2 8 1 2 1 

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

int main(){
    cout << "Введите кол-во элементов: ";
    int n = 0;
    cin >> n;
    cout << "Введите элементы:" << endl;
    node *st = NULL;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        push(st, x);
    }

    reverse(st);

    node *new_st = NULL;
    int max = st->inf;
    int num = 0;
    while (st){
        int x = pop(st);
        if (x > max){
            max = x;
        }
        if (x % 2 == 0){
            num = x;
        }
        push(new_st, x);
    }

    while (new_st){
        push(st, pop(new_st));
    }

    node *res = NULL;
    while (st){
        int x = pop(st);
        push(res, x);
        if (x == max){
            push(res, num);
        }
    }

    reverse(res);

    while (res){
        cout << pop(res) << " ";
    }
    cout << endl;

    return 0;
}