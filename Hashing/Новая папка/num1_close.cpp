// Метод деления по дню рождения
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int M = 61;

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

int fun_hash(int day){
    return day % M;
}

int linear_probe(int day, int i){
    return (fun_hash(day) + i) % M;
}

void print_emp(const Employee& e){
    cout << e.surname << " " << e.post << " " << e.day << "." << e.month << "." << e.year
         << " стаж: " << e.experience << " зарплата: " << e.salary << endl;
}

void add(Employee table[], const Employee& e){
    for (int i = 0; i < M; i++){
        int k = linear_probe(e.day, i);
        if (!table[k].busy){
            table[k] = e;
            table[k].busy = true;
            return;
        }
    }
    cout << "Таблица переполнена!" << endl;
}

void read_file(Employee table[]){
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Ошибка открытия input.txt" << endl;
        return;
    }
    Employee e;
    char dot1, dot2;
    while (fin >> e.surname >> e.post >> e.day >> dot1 >> e.month >> dot2 >> e.year >> e.experience >> e.salary){
        if (correct_date(e.day, e.month, e.year)){
            e.busy = false;
            add(table, e);
        }
    }
    fin.close();
}

void print_table(const Employee table[]){
    cout << "закрытая хэш таблица:" << endl;
    for (int i = 1; i < M; i++){
        cout << i << ": ";
        if (table[i].busy)
            cout << table[i].surname << " (день " << table[i].day << ")";
        else
            cout << "-";
        cout << endl;
    }
}

void search_day(const Employee table[], int day){
    bool found = false;
    cout << "поиск (день " << day << ")" << endl;
    for (int i = 0; i < M; i++){
        int k = linear_probe(day, i);
        if (!table[k].busy){
            break;
        }
        if (table[k].day == day){
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

    int day;
    cout << endl;
    cout << "Введите день для поиска: ";
    cin >> day;
    search_day(table, day);

    return 0;
}