// Расстановка скобок
// Реализовать любой из алгоритмов расстановки скобок при перемножении матриц, чтобы время работы было минимальным. 

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void prints(const vector<vector<int>>& split, int i, int j) {
    if (i == j) {
        cout << "A" << i;
        return;
    }
    cout << "(";
    prints(split, i, split[i][j]);
    cout << " x ";
    prints(split, split[i][j] + 1, j);
    cout << ")";
}

int main(){
    int n;
    cout << "Введите количество матриц: ";
    cin >> n;

    vector<long long> p(n + 1);

    cout << "Введите размеры: ";
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));
    vector<vector<int>> split(n + 1, vector<int>(n + 1, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;

            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }


    cout << "Минимальное число умножений: " << dp[1][n] << endl;
    cout << "Оптимальная расстановка скобок: ";

    prints(split, 1, n);

    cout << endl;

    return 0;
}