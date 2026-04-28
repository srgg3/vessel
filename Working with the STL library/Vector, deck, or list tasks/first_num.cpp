// Дан набор целых чисел. Заменить все минимальные числа нулем.

#include <iostream>
#include <vector>

using namespace std;

int main(){
    setlocale (LC_ALL, "russian");
    int n = 0;
    cout << "Введите кол-во в наборе целых чисел: ";
    cin >> n;

    vector<int> vec;
    int x = 0;
    for (int i = 0; i < n; i++){
        cout << i + 1 << " элемент = ";
        cin >> x;
        vec.push_back(x);
    }
    
    cout << "Старый: ";

    for (int x: vec){
        cout << x << " ";
    }

    cout << endl;
    cout << "Новый:  ";

    int min = *min_element(vec.begin(), vec.end());
    replace(vec.begin(), vec.end(), min, 0);
    
    for (int x: vec){
        cout << x << " ";
    }
    return 0;
}