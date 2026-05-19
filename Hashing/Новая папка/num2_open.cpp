// Основная — двойное хеширование, вспомогательная — метод умножения по зарплате
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

const int M = 8;
const double A = (sqrt(5) - 1) / 2;

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

int fun_hash(int salary){
    double val = salary * A;
    val = val - floor(val);
    return (int)(M * val);
}

void print_emp(const Employee& e){
    cout << e.surname << " " << e.post << " " << e.day << "." << e.month << "." << e.year
         << " стаж: " << e.experience << " зарплата: " << e.salary << endl;
}

void add(Node* table[], const Employee& e) {
    int k = fun_hash(e.salary);
    Node* p = create_node(e);
    p->next = table[k];
    if (table[k] != NULL)
        table[k]->prev = p;
    table[k] = p;
}

void read_file(Node* table[]) {
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Ошибка открытия input.txt" << endl;
        return;
    }
    Employee e;
    char dot1, dot2;
    while (fin >> e.surname >> e.post >> e.day >> dot1 >> e.month >> dot2 >> e.year >> e.experience >> e.salary) {
        if (correct_date(e.day, e.month, e.year)){
            add(table, e);
        }
    }
    fin.close();
}

void print_table(Node* table[]) {
    cout << "открытая хэш таблица:" << endl;
    for (int i = 0; i < M; i++) {
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

void search_salary(Node* table[], int salary) {
    int k = fun_hash(salary);
    Node* p = table[k];
    bool found = false;
    cout << "поиск (зарплата " << salary << ")" << endl;
    while (p) {
        if (p->data.salary == salary) {
            print_emp(p->data);
            found = true;
        }
        p = p->next;
    }
    if (!found){
        cout << "Не найдено." << endl;
    }
}

void delete_salary(Node* table[], int salary){
    int k = fun_hash(salary);
    Node* p = table[k];
    while (p) {
        Node* next = p->next;
        if (p->data.salary == salary){
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

    int salary;
    cout << endl;
    cout << "Введите зарплату для поиска: ";
    cin >> salary;
    search_salary(table, salary);

    cout << endl;
    cout << "Введите зарплату для удаления: ";
    cin >> salary;
    delete_salary(table, salary);
    print_table(table);

    return 0;
}