// Дана последовательность целых чисел. 
// Найти все такие цифры, которые встречаются в трехзначных числах, но не встречаются в двузначных. 
// Работать только с цифрами, которые встречаются в данной последовательности, а не со всеми цифрами от 0 до 9.

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
    int n = 0;
    cout << "Введите кол-во элементов последовательности: ";
    cin >> n;

    int x = 0;
    vector<int> vec;
    for (int i = 0; i < n; i++){
        cout << i + 1 << " элемент = ";
        cin >> x;
        vec.push_back(x);
    }

    set<int> mn;
    for (int x : vec){
        int x2 = abs(x);
        while (x2 != 0){
            mn.insert(x2 % 10);
            x2 = x2 / 10;
        }
    }

    vector<int> three_digit, two_digit;
    for (int x : vec){
        if (x < 1000 and x > 99){
            three_digit.push_back(x);
        }
        if (x < 100 and x > 9) {
            two_digit.push_back(x);
        }
    }

    set<int> digit_2, digit_3;
    for (int x : two_digit){
        int x2 = abs(x);
        while (x2 != 0){
            digit_2.insert(x2 % 10);
            x2 = x2 / 10;
        }
    }

    for (int x : three_digit){
        int x2 = abs(x);
        while (x2 != 0){
            digit_3.insert(x2 % 10);
            x2 = x2 / 10;
        }
    }

    set<int> res;
    for (int x : digit_3){
        if (!digit_2.count(x)){
            res.insert(x);
        }
    }

    for (int x : res){
        cout << x << " ";
    }
    return 0;
}