// Условия:
// 1) Должен быть список реальных слов (не менее 10) из 8-15 букв.

// 2) При запуске на экране должно быть слово, все буквы которого заменены нижним подчеркиванием, Должен быть выведен алфавит. 
// В ходе игры угаданные буквы вставляются на нужные места в загаданном слове и убираются(зачеркиваются) из алфавита.

// 3) Может быть два варианта игры:
//     1. Определяется максимальное число ходов и счетчик ходов. Игра завершается либо когда слово угадано, либо когда закончились ходы.
//     2. Либо с помощью слешей и тире рисуется человечек как в виселице. Игра заканчивается, когда либо угадано слово, 
//     либо человечек полностью нарисован.

// 4) У пользователя должен быть выбор:
//     1. Ввести слово целиком. Если угадал, то выиграл. Если нет, выводится сообщение об ошибке и игра завершается.
//     2. Ввести букву. Если угадал, буква ставится на нужное место и удаляется из алфавита. Если не угадал, выводится сообщение об ошибке, 
//     увеличивается счетчик ходов или рисуется очередной элемент виселицы.

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>


using namespace std;

void alphabet_print(const vector<char>& alfa, const vector<bool>& used){
    cout << endl;
    cout << "Алфавит:" << endl;
    for (int i = 0; i < alfa.size(); i++){
        if (used[i]){
            cout << "- ";
        } else {
            cout << alfa[i] << " ";
        }
    }
    cout << endl;
}

void word_print(const string& word){
    cout << endl;
    cout << "Слово: ";
    for (char c : word){
        cout << c << " ";
    }
    cout << endl;
}

int main(){
    srand(time(0));
    
    // vector<string> words;
    // ifstream file("file.txt");

    // if (!file.is_open()) {
    //     cout << "error :<" << endl;
    //     return 1;
    // }

    // string word;
    // while (file >> word) {
    //     words.push_back(word);
    // }

    // file.close();

    vector<string> words = {
        "beautiful", "chocolate", "tomorrow", "important", "education", 
        "different", "community", "fantastic", "knowledge", "telephone", 
        "character", "direction", "emergency", "passenger", "practical"
    };


    vector<char> alfa;
    for (char i = 'a'; i <= 'z'; i++){
        alfa.push_back(i);
    }

    vector<bool> used(alfa.size(), false);

    string secret = words[rand() % words.size()];
    string res(secret.length(), '_');

    int max = 7;
    int count = 0;

    while (true){
        word_print(res);
        alphabet_print(alfa, used);

        if (res == secret){
            cout << endl;
            cout << "Вы угадали слово: " << secret << endl;
            break;
        }

        if (count >= max){
            cout << endl;
            cout << "Ты проиграл! Секретным словом было: " << secret << endl;
            break;
        }

        cout << endl;
        cout << "1 - ввести слово целиком" << endl;
        cout << "2 - ввести букву" << endl;
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        if (choice == 1){
            string word;
            cout << "Введите слово: ";
            cin >> word;

            if (word == secret){
                cout << endl;
                cout << "Вы угадали слово: " << secret << endl;
            } else {
                cout << endl;
                cout << "Ты проиграл! Секретным словом было:" << secret << endl;
            }
            break;

        } else if (choice == 2){
            char ltr;
            cout << "Введите букву: ";
            cin >> ltr;

            bool ltr_found = false;

            for (int i = 0; i < alfa.size(); i++){
                if (alfa[i] == ltr and used[i] == false){
                    used[i] = true;
                    ltr_found = true;

                    bool correct = false;
                    for (int j = 0; j < secret.length(); j++){
                        if (secret[j] == ltr){
                            res[j] = ltr;
                            correct = true;
                        }
                    }

                    if (correct == false){
                        count++;
                        cout << endl;
                        cout << "Упс :( Error #" << count << endl;
                    } else {
                        cout << endl;
                        cout << "Правильно!" << endl;
                    }
                }
            }

            if (ltr_found == false){
                cout << endl;
                cout << "Уже использованная буква или неверный ввод!" << endl;
            }

        } else {
            cout << endl;
            cout << "Неверный выбор!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}