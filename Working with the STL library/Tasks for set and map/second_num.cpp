// Во входном файле задан набор слов и целых чисел, разделенных пробелами. Найти числа, встречающиеся ровно 𝑘 раз.

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

bool nums(const string& s){
    for (char c : s){
        if (isdigit(c) == false and c != '-'){
            return false;
        }
    }
    return true;
}

int main() {
    ifstream file("file.txt");
    int k = 0;
    cout << "Введите k = ";
    cin >> k;

    map<int, int> count;

    string word;
    while (file >> word){
        if (nums(word)){
            int num = stoi(word);
            count[num]++;
        }
    }
    
    file.close();
    
    cout << "Числа, встречающиеся ровно " << k << " раз: " << endl;

    for (auto x : count){
        if (x.second == k){
            cout << x.first << " ";
        }
    }
    return 0;
}