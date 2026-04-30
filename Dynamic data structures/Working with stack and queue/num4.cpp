// Создать стек, содержащий целые числа. Удалить все числа с максимальным количеством делителей. 
// Порядок следования в результате должен совпадать с порядком следования ввода.
//  Например, было 1 2 3 4 5 6 7 8 9. Стало 1 2 3 4 5 7 9 

#include <iostream>

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

int cnt_div(int x){
    int cnt = 0;
    for (int i = 1; i <= x; i++){
        if (x % i == 0){
            cnt++;
        }
    }
    return cnt;
}

int main(){
    node *st = NULL;
    int n;
    cout << "Введите кол-во элементов: ";
    cin >> n;

    cout << "Введите элементы:" << endl;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        push(st, x);
    }

    reverse(st);

    node *new_st = NULL;
    int max = 0;
    while (st){
        int x = pop(st);
        int k = cnt_div(x);
        if (k > max){
            max = k;
        }
        push(new_st, x);
    }

    while (new_st){
        push(st, pop(new_st));
    }

    node *res = NULL;
    while (st){
        int x = pop(st);
        if (cnt_div(x) != max){
            push(res, x);
        }
    }

    reverse(res);

    while (res){
        cout << pop(res) << " ";
    }
    return 0;
}