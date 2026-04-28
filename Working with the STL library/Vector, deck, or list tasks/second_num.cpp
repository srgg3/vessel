//  Даны две последовательности целых чисел. 
//  В первой последовательности удалить все элементы, кратные 𝑋. 
//  Во второй — заменить элементы, попадающие в интервал [𝑎, 𝑏] числом 𝑌. 
//  Отсортировать данные последовательности. Объединить их в одну отсортированную последовательность 
//  (оптимальным способом. Добавить в конец и потом отсортировать - не является оптимальным способом).

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    setlocale (LC_ALL, "russian");
    int n1 = 0;
    cout << "Введите кол-во элементов I последовательности: ";
    cin >> n1;

    int n2 = 0;
    cout << "Введите кол-во элементов II последовательности: ";
    cin >> n2;

    vector<int> vec1;
    vector<int> vec2;

    cout << "Первая последовательность: " << endl;
    int x1 = 0;
    for (int i = 0; i < n1; i++){
        cout << i + 1 << " элемент = ";
        cin >> x1;
        vec1.push_back(x1);
    }

    cout << "Вторая последовательность: " << endl;
    int x2 = 0;
    for (int i = 0; i < n2; i++){
        cout << i + 1 << " элемент = ";
        cin >> x2;
        vec2.push_back(x2);
    }

    cout << "Введите Х = ";
    int X = 0;
    cin >> X;

    vec1.erase(remove_if(vec1.begin(), vec1.end(), [X](int x){
        return x % X == 0;
    }), vec1.end());

    cout << "Введите a и b (через пробел): ";
    int a = 0, b = 0;
    cin >> a;
    cin >> b;

    cout << "Введите Y = ";
    int Y = 0;
    cin >> Y;
    
    for (int i = 0; i < vec2.size(); i++){
        if (vec2[i] >= a and vec2[i] <= b){
            replace(vec2.begin(), vec2.end(), vec2[i], Y);
        }
    }

    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());

    cout << "I последовательность: ";

    for (int x : vec1){
        cout << x << " ";
    }

    cout << endl;


    cout << "II последовательность: ";

    for (int x : vec2){
        cout << x << " ";
    }

    cout << endl;

    vector<int> vec;

    merge(vec1.begin(), vec1.end(),
        vec2.begin(), vec2.end(),
        back_inserter(vec));
    
    cout << "Итоговая последовательность: ";
    for (int x : vec){
        cout << x << " ";
    }
    cout << endl;

    return 0;
}