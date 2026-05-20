// Перемножение матриц
// Реализовать перемножение двух матриц, используя алгоритм Штрасена или Винограда.

#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 2;
    cout << "Введите матрицу A" << endl;
    vector<vector<int>> matrix1;
    for (int i = 0; i < n; i++){
        vector<int> matrix_in;
        for (int j = 0; j < n; j++){
            int a = 0;
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> a;
            matrix_in.push_back(a);
        }
        matrix1.push_back(matrix_in);
    }

    cout << "Введите матрицу B" << endl;
    vector<vector<int>> matrix2;
    for (int i = 0; i < n; i++){
        vector<int> matrix_in;
        for (int j = 0; j < n; j++){
            int a = 0;
            cout << "B[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> a;
            matrix_in.push_back(a);
        }
        matrix2.push_back(matrix_in);
    }

    int d = (matrix1[0][0] + matrix1[1][1]) * (matrix2[0][0] + matrix2[1][1]);
    int d1 = (matrix1[0][1] - matrix1[1][1]) * (matrix2[1][0] + matrix2[1][1]);
    int d2 = (matrix1[1][0] - matrix1[0][0]) * (matrix2[0][0] + matrix2[0][1]);
    int h1 = (matrix1[0][0] + matrix1[0][1]) * matrix2[1][1];
    int h2 = (matrix1[1][0] + matrix1[1][1]) * matrix2[0][0];
    int v1 = (matrix2[1][0] - matrix2[0][0]) * matrix1[1][1];
    int v2 = (matrix2[0][1] - matrix2[1][1]) * matrix1[0][0];
    
    vector<vector<int>> matrix_res(2, vector<int>(2));
    matrix_res[0][0] = d + d1 - h1 + v1;
    matrix_res[0][1] = h1 + v2;
    matrix_res[1][0] = h2 + v1;
    matrix_res[1][1] = d + d2 - h2 + v2;

    cout << "Ответ:" << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << matrix_res[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}