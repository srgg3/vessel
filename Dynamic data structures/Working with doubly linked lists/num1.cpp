// Создать двусвязный список, содержащий целые числа. Удалить первый и последний минимальный элемент. 
// Например, было 8 2 1 6 8 8 1 2 2 8 2 1. Стало 8 2 6 8 8 1 2 2 8 2.

#include <iostream>
using namespace std;

struct node{
    int inf;
    node *prev;
    node *next;
};


void push(node *&h, node *&t, int x){
    node *r = new node;
    r->inf = x;
    r->next = NULL;
    r->prev = t;
    if (!h){
        h = t = r;
    } else {
        t->next = r;
        t = r;
    }
}

void prints(node *h, node *t){
    node *p = h;
    while (p){
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

int find_min(node *h, node *t){
    int min_num = h->inf;
    node *p = h->next;
    while (p){
        if (p->inf < min_num){
            min_num = p->inf;
        }
        p = p->next;
    }
    return min_num;
}

node *find_first(node *h, node *t, int x){
    node *p = h;
    while (p){
        if (p->inf == x){
            break;
        }
        p = p->next;
    }
    return p;
}

node *find_last(node *h, node *t, int x){
    node *p = h;
    node *last = NULL;
    while (p){
        if (p->inf == x){
            last = p;
        }
        p = p->next;
    }
    return last;
}

void delete_node(node *&h, node *&t, node *r){
    if (r == h && r == t){
        h = t = NULL;
    } else if (r == h){
        h = h->next;
        if (h){
            h->prev = NULL;
        }
    } else if (r == t){
        t = t->prev;
        t->next = NULL;
    } else {
        r->next->prev = r->prev;
        r->prev->next = r->next;
    }
    if (!r) return;
    delete r;
}

void del_node(node *&h, node *&t){
    while (h){
        node *p = h;
        h = h->next;
        if (h){
            h->prev = NULL;
        }
        delete p;
    }
    t = NULL;
}

int main(){
    node *h = NULL;
    node *t = NULL;

    int n;
    cout << "Введите кол-во элементов: ";
    cin >> n;

    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        push(h, t, x);
    }

    int min_num = find_min(h, t);

    node *first_min = find_first(h, t, min_num);
    node *last_min = find_last(h, t, min_num);

    if (first_min && last_min){
        if (first_min == last_min){
            delete_node(h, t, first_min);
        } else {
            delete_node(h, t, last_min);
            delete_node(h, t, first_min);
        }
    }

    cout << "Результат: ";
    prints(h, t);

    del_node(h, t);

    return 0;
}