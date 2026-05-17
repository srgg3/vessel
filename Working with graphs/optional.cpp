// Дан неориентированный взвешенный граф. Найти кратчайшее расстояние от заданной вершины до всех остальных вершин. 
// Вывести не только длину пути, но и сам этот путь. Алгоритм выбираете самостоятельно.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int find_min_dist(vector<int> dist, vector<bool> visited, int n) {
    int min_dist = INT_MAX;
    int min_index = -1;
    for (int i = 0; i < n; i++){
        if (!visited[i] && dist[i] < min_dist){
            min_dist = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    int n = 0, m = 0;
    cout << "Введите кол-во вершин n = ";
    cin >> n;
    cout << "Введите кол-во ребер m = ";
    cin >> m;

    vector<vector<pair<int, int>>> graf(n);

    cout << "Введите ребра: " << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graf[u].push_back({v, w});
        graf[v].push_back({u, w});
    }

    int start;
    cout << "Введите стартовую вершину: ";
    cin >> start;

    vector<int> dist(n, INT_MAX);
    vector<int> prev(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = find_min_dist(dist, visited, n);
        if (u == -1) break;
        visited[u] = true;

        for (auto &edge : graf[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
        }
    }

    cout << "Результаты от вершины " << start << ":" << endl;
    for (int i = 0; i < n; i++){
        cout << "Вершина " << i << ": ";
        if (dist[i] == INT_MAX){
            cout << "error";
            continue;
        }
        cout << "расстояние = " << dist[i] << ", путь: ";

        vector<int> path;
        for (int v = i; v != -1; v = prev[v])
            path.push_back(v);
        reverse(path.begin(), path.end());

        for (size_t j = 0; j < path.size(); j++){
            cout << path[j];
            if (j + 1 < path.size()){
                cout << " - ";
            }
        }
        cout << endl;
    }

    return 0;
}