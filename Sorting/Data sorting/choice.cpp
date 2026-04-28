#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

ifstream in("input.txt");
ofstream out("output_choice.txt");

struct date{
    int day = 0, month = 0, year = 0;
};

struct people{
    string surname;
    string post;
    date date_of_birth;
    int experience;
    int salary;
};

date Str_to_Date(string str){
    date x;
    x.day = stoi(str.substr(0, 2));
    x.month = stoi(str.substr(3, 2));
    x.year = stoi(str.substr(6, 4));
    return x;
}

vector<people> inFile(){
    vector<people> ppl;
    string line;

    while (getline(in, line)){
        if (line.empty()){
            continue;
        }

        stringstream ss(line);
        people temp;
        if (!(ss >> temp.surname)){
            continue;
        }

        string word, birth;
        vector<string> post_words;

        while (ss >> word){
            if (word.size() == 10 and word[2] == '.' and word[5] == '.'){
                birth = word;
                break;
            }
            post_words.push_back(word);
        }

        if (birth.empty()){
            continue;
        }

        temp.post = "";
        for (size_t i = 0; i < post_words.size(); i++){
            if (i > 0){
                temp.post += " ";
            }
            temp.post += post_words[i];
        }

        temp.date_of_birth = Str_to_Date(birth);
        if (!(ss >> temp.experience >> temp.salary)){
            continue;
        }

        ppl.push_back(temp);
    }
    return ppl;
}

bool comparison(people a, people b){
    if (a.salary < b.salary){
        return true;
    }
    if (a.salary == b.salary and a.date_of_birth.year < b.date_of_birth.year){
        return true;
    }
    if (a.salary == b.salary and a.date_of_birth.year == b.date_of_birth.year and a.experience < b.experience){
        return true;
    }
    return false;
}

void choice_sort(vector<people>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (comparison(a[j], a[min])) {
                min = j;
            }
        }
        if (min != i) {
            swap(a[i], a[min]);
        }
    }
}

void max_len(vector<people>& ppl, int& max_sur, int& max_post){
    max_sur = 0;
    max_post = 0;
    for (auto& p : ppl) {
        if (p.surname.size() > max_sur){
            max_sur = p.surname.size();
        }
        if (p.post.size() > max_post){
            max_post = p.post.size();
        }
    }
}

void print(people x, int max_sur, int max_post){
    out << x.surname;
    int spaces = max_sur / 2 - x.surname.size() / 2;
    out << string(spaces + 2, ' ');

    out << x.post;
    spaces = max_post - x.post.size();
    out << string(spaces + 2, ' ');

    if (x.date_of_birth.day < 10){
        out << "0";
    }
    out << x.date_of_birth.day << ".";

    if (x.date_of_birth.month < 10){
        out << "0";
    }
    out << x.date_of_birth.month << ".";

    out << x.date_of_birth.year;

    out << "  ";

    out << left << setw(6) << x.experience;
    out << left << setw(10) << x.salary << endl;
}

int main(){
    vector<people> x = inFile();
    choice_sort(x);
    int max_sur, max_post;
    max_len(x, max_sur, max_post);
    for (int i = 0; i < x.size(); i++)
        print(x[i], max_sur, max_post);
    return 0;
}