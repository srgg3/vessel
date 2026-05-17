// Дан ориентированный граф. Если это возможно, реализовать топологическую сортировку
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> topological_sort(vector<vector<int>> graph, int n) {
    vector<int> in_degree(n, 0);

    for (int i = 0; i < n; i++){
        for (int v : graph[i]){
            in_degree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++){
        if (in_degree[i] == 0){
            q.push(i);
        }
    }

    vector<int> order;
    while (!q.empty()){
        int k = q.front();
        q.pop();
        order.push_back(k);

        for (int v : graph[k]){
            in_degree[v]--;
            if (in_degree[v] == 0){
                q.push(v);
            }
        }
    }

    if (order.size() != n){
        return {};
    }
    return order;
}

int main() {
    int n, m;
    cout << "Введите кол-во вершин n = ";
    cin >> n;
    cout << "Введите кол-во ребер m = ";
    cin >> m;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    vector<int> sorted = topological_sort(graph, n);

    if (sorted.empty()){
        cout << "Ошибка";
    } else {
        for (size_t i = 0; i < sorted.size(); i++){
            cout << sorted[i];
            if (i + 1 < sorted.size()){
                cout << " - ";
            }
        }
        cout << endl;
    }

    return 0;
}