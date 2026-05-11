// Дан невзвешенный граф неориентированный граф. Найти кратчайший путь между вершинами A и В.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
    int inf;
    node* next;
};

void push(node *&h, node *&t, int x) {
    node *r = new node;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        h = t = r;
    } else {
        t->next = r;
        t = r;
    }
}

int pop(node *&h, node *&t) {
    node* r = h;
    int num = h->inf;
    h = h->next;
    if (!h) t = NULL;
    delete r;
    return num;
}

vector<int> the_shortest_way(vector<vector<int>> graph, int start, int end){
    int n = graph.size();
    vector<int> dist(n, -1);
    vector<int> prev(n, -1);
    node* qh = NULL;
    node* qt = NULL;

    dist[start] = 0;
    push(qh, qt, start);

    while (!(qh == NULL)) {
        int v = pop(qh, qt);
        if (v == end) break;
        for (int to : graph[v]) {
            if (dist[to] == -1) {
                dist[to] = dist[v] + 1;
                prev[to] = v;
                push(qh, qt, to);
            }
        }
    }

    vector<int> path;
    if (dist[end] == -1) return path;
    for (int v = end; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}


int main() {
    int n = 0, m = 0;
    cout << "Введите кол-во вершин n = ";
    cin >> n;
    cout << "Введите кол-во ребер m = ";
    cin >> m;

    vector<vector<int>> graph;
    graph.resize(n);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int a = 0, b = 0;
    cout << "Введите вершину a: ";
    cin >> a;
    cout << "Введите вершину b: ";
    cin >> b;

    if (a < 0 || a >= n || b < 0 || b >= n) {
        cout << "a или b вне диап-на" << endl;
        return 0;
    }

    vector<int> s = the_shortest_way(graph, a, b);
    if (s.empty()) {
        cout << "пути между " << a << " и " << b << " не существует." << endl;
    } else {
        cout << "кратчайший путь: ";
        for (size_t i = 0; i < s.size(); i++) {
            cout << s[i];
        }
        cout << "Длина пути: " << s.size() - 1 << endl;
    }

    return 0;
}