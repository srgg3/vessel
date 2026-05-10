// Дан неориентированный граф. Выяснить, является ли граф связным.

#include <iostream>
#include <vector>

using namespace std;

void dfs(int v, vector<vector<int>> a, vector<bool> visited) {
    visited[v] = true;
    for (int n : a[v]) {
        if (!visited[n]) {
            dfs(n, a, visited);
        }
    }
}

int main() {
    int n = 0, m = 0;
    cout << "Введите кол-во вершин n = ";
    cin >> n;
    cout << "Введите кол-во ребер m = ";
    cin >> m;

    vector<vector<int>> graf(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graf[u].push_back(v);
        graf[v].push_back(u);
    }

    vector<bool> visited(n, false);

    dfs(0, graf, visited);

    bool connected = true;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            connected = false;
            break;
        }
    }

    if (connected) {
        cout << "Граф связный" << endl;
    } else {
        cout << "Граф несвязный" << endl;
    }

    return 0;
}