// Дан неориентированный граф. Вывести количество вершин, смежных с данной.

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

    int x = 0;
    cout << "Введите вершину x = ";
    cin >> x;

    if (x < 0 || x >= n){
        cout << "x вне диап-на";
        return 0;
    }
    cout << "Ответ: " << count(graf, x);
    return 0;
}