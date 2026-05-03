// Нечетные строки по убыванию, четные по возрастанию помощью гномьей сортировки.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

ifstream in("input.txt");
ofstream out("output_dwarves.txt");

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

void gnom(vector<int>& a, int k){
    int i = 1;
    int n = a.size();

    while (i < n){
        if (i == 0){
            i++;
        }
        bool change;
        if (k % 2 != 0){
            change = a[i - 1] <= a[i];
        } else {
            change = a[i - 1] >= a[i];
        }

        if (change){
            i++;
        } else {
            swap(a[i], a[i - 1]);
            i--;
        }
    }
}


int main(){
    vector<vector<int>> mas = inFile();
    for(int i = 0; i < mas.size(); i++){
        gnom(mas[i], i);
    }
    for (int i = 0; i < mas.size(); i++){
        for (int j = 0; j < mas[i].size(); j++){
            out << mas[i][j] << " ";
        }
        out << endl;
    }

    return 0;
}