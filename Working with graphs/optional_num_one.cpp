// Дан неориентированный граф. Вывести Эйлеров путь или Эйлеров цикл, если он существует.
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs(int v, vector<vector<int>> graf, vector<bool>& visited) {
    visited[v] = true;
    for (int to : graf[v]) {
        if (!visited[to])
            dfs(to, graf, visited);
    }
}

bool is_сonnected(vector<vector<int>> graf, int n) {
    int start = -1;
    for (int i = 0; i < n; i++){
        if (!graf[i].empty()){
            start = i;
            break;
        }
    }

    if (start == -1){
        return true;
    }

    vector<bool> visited(n, false);
    dfs(start, graf, visited);
    for (int i = 0; i < n; i++){
        if (!graf[i].empty() && !visited[i]){
            return false;
        }
    }

    return true;
}


vector<int> euler(vector<vector<int>> graf, int start, bool isCycle) {
    stack<int> st;
    vector<int> path;
    st.push(start);
    while (!st.empty()) {
        int v = st.top();
        if (!graf[v].empty()) {
            int u = graf[v].back();
            graf[v].pop_back();
            auto it = find(graf[u].begin(), graf[u].end(), v);
            if (it != graf[u].end())
                graf[u].erase(it);
            st.push(u);
        } else {
            path.push_back(v);
            st.pop();
        }
    }
    reverse(path.begin(), path.end());
    return path;
}


int main() {
    int n, m;
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

    vector<int> degree(n, 0);
    for (int i = 0; i < n; i++)
        degree[i] = graf[i].size();

    vector<int> odd_vertices;
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 == 1)
            odd_vertices.push_back(i);
    }

    if (!(odd_vertices.empty() || odd_vertices.size() == 2)) {
        cout << "Эйлеров путь/цикл не существует.";
        return 0;
    }

    if (!is_сonnected(graf, n)){
        cout << "Граф несвязный, Эйлеров путь/цикл не существует.";
        return 0;
    }

    bool isCycle = odd_vertices.empty();
    int startVertex = 0;
    if (!isCycle) {
        startVertex = odd_vertices[0];
    } else {
        for (int i = 0; i < n; i++) {
            if (!graf[i].empty()) {
                startVertex = i;
                break;
            }
        }
    }

    vector<vector<int>> graphCopy = graf;

    if (!isCycle) {
        int v1 = odd_vertices[0], v2 = odd_vertices[1];
        graphCopy[v1].push_back(v2);
        graphCopy[v2].push_back(v1);
    }

    vector<int> eulerPath = euler(graphCopy, startVertex, isCycle);

    if (!isCycle) {
        int v1 = odd_vertices[0], v2 = odd_vertices[1];
        int k = -1;
        for (size_t i = 0; i + 1 < eulerPath.size(); i++) {
            if ((eulerPath[i] == v1 && eulerPath[i + 1] == v2) || (eulerPath[i] == v2 && eulerPath[i + 1] == v1)) {
                k = i;
                break;
            }
        }
        if (k != -1) {
            vector<int> realPath;
            for (size_t i = k + 1; i < eulerPath.size(); i++)
                realPath.push_back(eulerPath[i]);
            for (size_t i = 1; i <= (size_t)k; i++)
                realPath.push_back(eulerPath[i]);
            eulerPath = realPath;
        }
    }

    if (isCycle) {
        cout << "Эйлеров цикл:" << endl;;
    } else {
        cout << "Эйлеров путь:" << endl;
    }

    for (size_t i = 0; i < eulerPath.size(); ++i) {
        cout << eulerPath[i];
        if (i + 1 < eulerPath.size()) cout << " - ";
    }
    cout << endl;

    return 0;
}