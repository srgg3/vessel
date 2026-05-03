// Граф представлен в виде списка смежности. Реализовать обход в ширину, используя очередь, 
// и нерекурсивный обход в глубину.

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

void add(node* gr[], char u, char v){
    node* p = new node;
    p->inf = v;
    p->next = gr[u];
    gr[u] = p;
    
    p = new node;
    p->inf = u;
    p->next = gr[v];
    gr[v] = p;
}

void wide_bypass(char start, node* gr[], bool usi[], int size){
    char queue[100];
    int h = 0, t = 0;
    
    queue[t++] = start;
    usi[start] = true;
    cout << start << " ";
    
    while (h < t){
        char u = queue[h++];
        for (node* p = gr[u]; p; p = p->next){
            char v = p->inf;
            if (!usi[v]){
                usi[v] = true;
                queue[t++] = v;
                cout << v << " ";
            }
        }
    }
}

void non_recursive_bypass(char start, node* gr[], bool usi[], int size){
    node* st = NULL;
    push(st, start);
    usi[start] = true;
    cout << start << " ";
    
    while (st) {
        char u = st->inf;
        bool found = false;
        for (node *p = gr[u]; p; p = p->next){
            char v = p->inf;
            if (usi[v] == false){
                usi[v] = true;
                push(st, v);
                cout << v << " ";
                found = true;
                break;
            }
        }
        if (found == false){
            char dummy = pop(st);
        }
    }
}

int main(){
    int n, m;
    cout << "Введите количество вершин и рёбер: ";
    cin >> n >> m;
    
    node* gr[128] = {NULL};
    
    cout << "Введите рёбра:" << endl;
    for (int i = 0; i < m; i++) {
        char u, v;
        cin >> u >> v;
        add(gr, u, v);
    }
    
    char start;
    cout << "Введите стартовую вершину: ";
    cin >> start;
    
    bool usi_wide_bypass[128] = {false};
    cout << "обход в ширину: ";
    for (char i = 0; i < 128; i++){
        if (gr[i] != NULL and usi_wide_bypass[i] == false){
            wide_bypass(i, gr, usi_wide_bypass, 128);
        }
    }
    cout << endl;
    
    bool usi_non_recursive_bypass[128] = {false};
    cout << "нерекурсивный обход: ";
    for (char i = 0; i < 128; ++i){
        if (gr[i] != NULL and usi_non_recursive_bypass[i] == false){
            non_recursive_bypass(i, gr, usi_non_recursive_bypass, 128);
        }
    }
    cout << endl;
    return 0;
}