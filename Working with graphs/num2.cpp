// Дан ориентированный граф. Вставить в граф ребро, соединяющее вершины A и B.

#include <iostream>
#include <vector>

using namespace std;


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
        graf[u].push_back(v);
    }

    cout << "Граф:" << endl;
    for (int i = 0; i < n; i++){
        cout << i << ": ";
        for (int to : graf[i]){
            cout << to << " ";
        }
        cout << endl;
    }

    int a = 0, b = 0;
    cout << "Введите a и b:" << endl;
    cin >> a >> b;
    if (a >= 0 && a < n && b >= 0 && b < n) {
        graf[a].push_back(b);
        cout << "вершина добавлена" << endl;
    } else {
        cout << "вершина вне диап-на" << endl;
    }

    cout << "Граф:" << endl;
    for (int i = 0; i < n; i++){
        cout << i << ": ";
        for (int to : graf[i]){
            cout << to << " ";
        }
        cout << endl;
    }

    return 0;
}