#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

ifstream in("input.txt");
ofstream out("output_shell.txt");

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

bool cmp(people &a, people &b){
    if (a.post != b.post)
        return a.post < b.post;
    return a.surname < b.surname;
}

void shell_sort(vector<people>& a){
    int n = a.size();

    for (int step = n / 2; step > 0; step /= 2){
        for (int i = step; i < n; i++){
            people tmp = a[i];
            int j = i;

            while (j >= step and cmp(tmp, a[j - step])){
                a[j] = a[j - step];
                j -= step;
            }
            a[j] = tmp;
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

    out << (x.date_of_birth.day < 10 ? "0" : "") << x.date_of_birth.day << "."
        << (x.date_of_birth.month < 10 ? "0" : "") << x.date_of_birth.month << "."
        << x.date_of_birth.year;

    out << "  ";

    out << left << setw(6) << x.experience;
    out << left << setw(10) << x.salary << endl;
}

int main(){
    vector<people> x = inFile();
    shell_sort(x);
    int max_sur, max_post;
    max_len(x, max_sur, max_post);
    for (int i = 0; i < x.size(); i++)
        print(x[i], max_sur, max_post);
    return 0;
}