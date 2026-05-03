// Создать двусвязный список из целых чисел. 
// Удалить все повторяющиеся элементы, оставив только их первые вхождения. 
// Например, было 1 2 2 1 3 4 5 1 2 5 4 3 5. Стало 1 2 3 4 5.

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
    delete r;
}

void rm_dubl(node *&h, node *&t){
    node *p = h;

    while (p){
        node *r = p->next;

        while (r){
            node *c = r->next;

            if (r->inf == p->inf){
                delete_node(h, t, r);
            }

            r = c;
        }

        p = p->next;
    }
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

    rm_dubl(h, t);

    cout << "Результат: ";
    prints(h, t);

    del_node(h, t);
    return 0;
}