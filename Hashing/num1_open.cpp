// Метод деления по дню рождения
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

const int M = 31;

struct Employee {
    string surname, post;
    int day, month, year;
    int experience, salary;
};

struct Node {
    Employee data;
    Node* prev;
    Node* next;
};

Node* create_node(const Employee& e){
    Node* p = new Node;
    p->data = e;
    p->prev = NULL;
    p->next = NULL;
    return p;
}

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

void print_emp(const Employee& e){
    cout << e.surname << " " << e.post << " " << e.day << "." << e.month << "." << e.year << " стаж: " << e.experience << " зарплата: " << e.salary << endl;
}

void add(Node* table[], const Employee& e){
    int k = fun_hash(e.day);
    Node* p = create_node(e);
    p->next = table[k];
    if (table[k] != NULL)
        table[k]->prev = p;
    table[k] = p;
}

void read_file(Node* table[]){
    ifstream fin("input.txt");
    if (!fin){
        cout << "Ошибка открытия input.txt";
        return;
    }
    Employee e;
    char dot1, dot2;
    while (fin >> e.surname >> e.post >> e.day >> dot1 >> e.month >> dot2 >> e.year >> e.experience >> e.salary){
        if (correct_date(e.day, e.month, e.year)){
            add(table, e);
        }
    }
    fin.close();
}

void print_table(Node* table[]){
    cout << "открытая хэш таблица:" << endl;
    for (int i = 1; i < M; i++) {
        cout << i << ": ";
        Node* p = table[i];
        if (!p) cout << "-";
        while (p) {
            cout << p->data.surname << " ";
            p = p->next;
        }
        cout << endl;
    }
}

void search_day(Node* table[], int day) {
    int k = fun_hash(day);
    Node* p = table[k];
    bool found = false;
    cout << "поиск (день " << day << ")" << endl;
    while (p) {
        if (p->data.day == day) {
            print_emp(p->data);
            found = true;
        }
        p = p->next;
    }
    if (!found){
        cout << "-" << endl;
    }
}

void delete_day(Node* table[], int day){
    int k = fun_hash(day);
    Node* p = table[k];
    while (p){
        Node* next = p->next;
        if (p->data.day == day){
            if (p->prev){
                p->prev->next = p->next;
            } else { 
                table[k] = p->next;
            }
            if (p->next){
                p->next->prev = p->prev;
            }
            delete p;
        }
        p = next;
    }
}

int main(){
    Node* table[M] = {NULL};
    read_file(table);
    print_table(table);

    int day;
    cout << endl;
    cout << "Введите день для поиска: ";
    cin >> day;
    search_day(table, day);

    cout << endl;
    cout << "Введите день для удаления: ";
    cin >> day;
    delete_day(table, day);
    print_table(table);

    return 0;
}