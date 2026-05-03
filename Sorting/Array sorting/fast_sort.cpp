// Столбцы по возрастанию с помощью быстрой сортировки.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

ifstream in("input.txt");
ofstream out("output_fast.txt");

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

void quickly(vector<int>& a, int l, int r){
    int i = l;
    int j = r;

    int sup = a[(l + r) / 2];

    while (i <= j){
        while (a[i] < sup){
            i++;
        }
        while (a[j] > sup){
            j--;
        }
        if (i <= j){
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (l < j){
        quickly(a, l, j);
    }

    if (i < r){
        quickly(a, i, r);
    }
}


int main(){
    vector<vector<int>> mas = inFile();
    int n = mas.size();

    for(int i = 0; i < n; i++){
        vector<int> mas2;
        for(int j = 0; j < n; j++){
            mas2.push_back(mas[j][i]);
        }
        quickly(mas2, 0, n - 1);
        for(int j = 0; j < n; j++){
            mas[j][i] = mas2[j];
        }
    }

    for (int i = 0; i < mas.size(); i++) {
        for (int j = 0; j < mas[i].size(); j++) {
            out << mas[i][j] << " ";
        }
        out << endl;
    }

    return 0;
}