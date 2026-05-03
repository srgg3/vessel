// Дана шахматная доска. 
// Вывести кратчайший путь конем от клетки А до клетки В. 
// Должны быть введены две клетки в виде, например, А2 и Е6. 
// Путь должен быть выведен в виде списка клеток А2 В4 С6 D8 E6

#include <iostream>

using namespace std;

struct node
{
    int x, y;
    node* next;
};

struct queus
{
    node *inf;
    queus *next;
};

void push(queus *&h, node *x){
    queus *r = new queus;
    r->inf = x;
    r->next = h;
    h = r;
}

node* pop(queus *&h){
    node *x = h->inf;
    queus *r = h;
    h = h->next;
    delete r;
    return x;
}

int main(){
    string s1, s2;
    cin >> s1 >> s2;
    int x1 = s1[0] - 'A';
    int y1 = s1[1] - '1';
    int x2 = s2[0] - 'A';
    int y2 = s2[1] - '1';

    bool usi[8][8] = {false};
    
    node *q[64];
    int h = 0, t = 0;
    node *start = new node{x1, y1, NULL};
    q[t++] = start;
    usi[x1][y1] = true;
    int dx[8] = {1, 2, 1, 2, -1, -2, -1, -2};
    int dy[8] = {2, 1, -2, -1, 2, 1, -2, -1};

    node *finish = NULL;

    while (h != t){
        node *c = q[h++];
        h %= 64;
        
        if (c->x == x2 and c->y == y2){
            finish = c;
            break;
        }

        for (int i = 0; i < 8; i++){
            int x1 = c->x + dx[i];
            int y1 = c->y + dy[i];
            if (x1 >= 0 and x1 < 8 and y1 >= 0 and y1 < 8 and usi[x1][y1] == false){
                usi[x1][y1] = true;
                node *n = new node{x1, y1, c};
                q[t++] = n;
                t %= 64;
            }
        }
    }
    
    queus *st = NULL;
    node *p = finish;
    while (p){
        push(st, p);
        p = p->next;
    }

    while (st){
        node *c = pop(st);
        cout << char(c->x + 'A') << c->y + 1 << " ";
    }
    cout << endl;
    return 0;
}

