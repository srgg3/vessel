// Ханойские башни
// Реализовать игру Ханойские башни.

#include <iostream>
using namespace std;

void hanoi(int n, char one, char two, char three) {
    if (n == 1){
        cout << "Переложить диск 1 с " << one << " на " << two << endl;
        return;
    }
    hanoi(n - 1, one, three, two);
    cout << "Переложить диск " << n << " с " << one << " на " << two << endl;
    hanoi(n - 1, three, two, one);
}

int main() {
    int n;
    cout << "Введите кол-во дисков: ";
    cin >> n;

    cout << "Последовательность ходов:" << endl;
    hanoi(n, 'A', 'C', 'B');

    return 0;
}