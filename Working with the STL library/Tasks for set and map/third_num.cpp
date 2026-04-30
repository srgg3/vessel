// Дан текст, состоящий из предложений, разделенных знаками препинания из набора «.?!». 
// Предложения в свою очередь состоят из слов, отделенных друг от друга пробелами. 
// Найти слова (без учета регистра), которые встречаются одновременно и в повествовательных, и в восклицательных предложениях

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

string lower_regist(string s){
    for (int i = 0; i < s.length(); i++){
        s[i] = tolower(s[i]);
    }
    return s;
}

int main(){
    set<string> tochka;
    set<string> vosk;
    set<string> res;

    string str = "";
    cout << "Введите текст: ";
    getline(cin, str);

    string znak = ".?!";
    int pos = 0;

    while (true){
        int k = str.find_first_of(znak, pos);
        if (k == string::npos){
            break;
        }
        char tmp = str[k];
        string temp = str.substr(pos, k - pos);
        temp += " ";

        int pos2 = 0;
        while (true){
            int k1 = temp.find_first_of(" ", pos2);
            if (k1 == string::npos){
                break;
            }
            string word = temp.substr(pos2, k1 - pos2);
            if (word != ""){
                word = lower_regist(word);
                if (tmp == '.'){
                    tochka.insert(word);
                } else if (tmp == '!'){
                    vosk.insert(word);
                }
            }

            pos2 = k1 + 1;
        }
        pos = k + 1;
    }

    set_intersection(tochka.begin(), tochka.end(), vosk.begin(), vosk.end(), inserter(res, res.begin()));

    cout << "Ответ:" << endl;

    for (string word : res){
        cout << word << endl;
    }

    return 0;
}