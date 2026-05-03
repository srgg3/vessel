//Диагонали, параллельные побочной по убыванию с помощью сортировки перемешиванием.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

ifstream in("input.txt");
ofstream out("output_mixing.txt");

vector<vector<int>> inFile(){
    vector<vector<int>> mas;
    string l;
    while(getline(in, l)){
        vector<int> mas2;
        stringstream ss(l);
        int n;
        while (ss >> n){
            mas2.push_back(n);
        }
        mas.push_back(mas2);
    }
    return mas;
}

void mixing(vector<int>& a){
    int begin = -1;
    int end = a.size() - 1;
    bool swa = true;

    while (swa){
        swa = false;
        begin++;
        for (int j = begin; j < end; j++){
            if (a[j] < a[j + 1]){
                swap(a[j], a[j + 1]);
                swa = true;
            }
        }
        if (swa == false){
            break;
        }
        swa = false;
        end--;
        for (int j = end; j > begin; j--){
            if (a[j - 1] < a[j]){
                swap(a[j - 1], a[j]);
                swa = true;
            }
        }
    }
}

int main(){
    vector<vector<int>> mas = inFile();
    int n = mas.size();

    for (int k = 0; k <= 2 * (n - 1); k++){
        vector<int> diag;
        vector<pair<int,int>> pos;

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (i + j == k){
                    diag.push_back(mas[i][j]);
                    pos.push_back({i,j});
                }
            }
        }

        if (diag.size() > 1){
            mixing(diag);
        }

        for (int i = 0; i < diag.size(); i++){
            mas[pos[i].first][pos[i].second] = diag[i];
        }
    }

    for (int i = 0; i < mas.size(); i++){
        for (int j = 0; j < mas[i].size(); j++){
            out << mas[i][j] << " ";
        }
        out << endl;
    }

    return 0;
}