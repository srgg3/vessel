// Основная — двойное хеширование, вспомогательная — метод умножения по зарплате
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

const int M = 61;
const double A = (sqrt(5) - 1) / 2;

struct Employee {
    string surname, post;
    int day, month, year;
    int experience, salary;
    bool busy;
};

bool correct_date(int d, int m, int y){
    if (y < 1926 || y > 2026){
        return false;
    }
    if (m < 1 || m > 12){
        return false;
    }
    if (d < 1 || d > 31){
        return false;
    }
    return true;
}

int hash1(int salary){
    double val = salary * A;
    val = val - floor(val);
    return (int)(M * val);
}

int hash2(int salary) {
    return 1 + (salary % (M - 1));
}

int double_hash(int salary, int i) {
    return (hash1(salary) + i * hash2(salary)) % M;
}

void print_emp(const Employee& e) {
    cout << e.surname << " " << e.post << " " << e.day << "." << e.month << "." << e.year
         << " стаж: " << e.experience << " зарплата: " << e.salary << endl;
}

void add(Employee table[], const Employee& e) {
    for (int i = 0; i < M; i++) {
        int k = double_hash(e.salary, i);
        if (!table[k].busy) {
            table[k] = e;
            table[k].busy = true;
            return;
        }
    }
    cout << "Таблица переполнена!" << endl;
}

void read_file(Employee table[]) {
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Ошибка открытия input.txt" << endl;
        return;
    }
    Employee e;
    char dot1, dot2;
    while (fin >> e.surname >> e.post >> e.day >> dot1 >> e.month >> dot2 >> e.year >> e.experience >> e.salary){
        if (correct_date(e.day, e.month, e.year)) {
            e.busy = false;
            add(table, e);
        }
    }
    fin.close();
}

void print_table(const Employee table[]) {
    cout << "закрытая хэш таблица:" << endl;
    for (int i = 0; i < M; i++) {
        cout << i << ": ";
        if (table[i].busy)
            cout << table[i].surname << " (з/п " << table[i].salary << ")";
        else
            cout << "-";
        cout << endl;
    }
}

void search_salary(const Employee table[], int salary) {
    bool found = false;
    cout << "поиск (зарплата " << salary << ")" << endl;
    for (int i = 0; i < M; i++){
        int k = double_hash(salary, i);
        if (!table[k].busy) break;
        if (table[k].salary == salary){
            print_emp(table[k]);
            found = true;
        }
    }
    if (!found){
        cout << "Не найдено." << endl;
    }
}

int main(){
    Employee table[M];
    for (int i = 0; i < M; i++){
        table[i].busy = false;
    }
    read_file(table);
    print_table(table);

    int salary;
    cout << endl;
    cout << "Введите зарплату для поиска: ";
    cin >> salary;
    search_salary(table, salary);

    return 0;
}