// Даны  два списка из целых чисел. Размеры обоих списков одинаковые. 
// Используя библиотеки numeric и functional, найти количество попарно совпадающих элементов.

#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

int main(){
    setlocale (LC_ALL, "russian");
    int n = 0;
    cout << "Введите кол-во элементов последовательностей: ";
    cin >> n;

    vector<int> vec1;
    vector<int> vec2;

    cout << "I последовательность: " << endl;
    int x1 = 0;
    for (int i = 0; i < n; i++){
        cout << i + 1 << " элемент = ";
        cin >> x1;
        vec1.push_back(x1);
    }

    cout << "II последовательность: " << endl;
    int x2 = 0;
    for (int i = 0; i < n; i++){
        cout << i + 1 << " элемент = ";
        cin >> x2;
        vec2.push_back(x2);
    }

    int count = inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0, plus<int>(),
        [](int a, int b){
            return a == b;
        });

    cout << "Ответ: " << count << endl;

    return 0;
}