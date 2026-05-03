// Используя кольцевой список, решить задачу Иосифа: 
// Дан список из 𝑁 чисел. Удалять каждый 𝐾-ый элемент до тех пор, пока не останется единственный элемент.
// Вывести его на экран.

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

void circle(node *&h, node *&t){
    if (h && t){
        t->next = h;
        h->prev = t;
    }
}

int result(node *&h, node *&t, int x){
    node *p = h;

    while (p != p->next){
        for (int i = 1; i < x; i++){
            p = p->next;
        }

        node *r = p;

        if (r == h){
            h = h->next;
        }
        if (r == t){
            t = t->prev;
        }

        r->prev->next = r->next;
        r->next->prev = r->prev;

        p = r->next;

        delete r;
    }

    h = t = p;
    return p->inf;
}

int main(){
    node *h = NULL;
    node *t = NULL;

    int n;
    cout << "Введите кол-во элементов: ";
    cin >> n;

    int k;
    cout << "Введите шаг: ";
    cin >> k;

    for (int i = 1; i <= n; i++){
        push(h, t, i);
    }

    circle(h, t);

    int res = result(h, t, k);
    cout << "Результат: " << res << endl;
    if (h){
        h->next = NULL;
        h->prev = NULL;
    }

    del_node(h, t);
    return 0;
}