// Дан неориентированный граф. Подсчитать степень каждой вершины.

#include <iostream>
#include <vector>

using namespace std;

int count(vector<vector<int>> a, int x) {
    return a[x].size();
}


int main(){
    int n = 0, m = 0;
    cout << "Введите кол-во вершин n = ";
    cin >> n;
    cout << "Введите кол-во ребер m = ";
    cin >> m;

    vector<vector<int>> graf(n);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        graf[v].push_back(u);
        graf[u].push_back(v);
    }

    for (int i = 0; i < n; i++){
        cout << "Вершина " << i << ": " << count(graf, i) << endl;
    }

    return 0;
}