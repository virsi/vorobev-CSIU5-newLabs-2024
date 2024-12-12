#include <iostream>
#include <fstream>
#include "Main.h"
using namespace std;

int PrintMenu() {
    cout << "1 - добавление слова в словарь \n"
    << "2 - удаление слова из словаря \n"
    << "3 - перевод слов с английского на русский \n"
    << "4 - перевод слов с русского на английский \n"
    << "5 - вывод на экран словаря  \n"
    << "6 - вывод словаря в файл \n"
    << "7 - выход из программы\n";

    int choose;
    cout << "\nВведите число от 1 до 7: ";
    cin >> choose;
    return choose;
}

// Возвращает true, если слова совпадают, false в обратном случае
bool Equals(char word1[], char word2[]) {
    for (int i = 0; i < l_word; i++) {
        if (word1[i] != word2[i])
            return false;
        if (word1[i] == '\0' && word2[i] == '\0')
            return true;
    }

    return true;
}

// Сравнивает два слова (посимвольно)
bool Compare(char word1[], char word2[]) {
    for (int i = 0; word1[i] != '\0' || word2[i] != '\0'; ++i) {
        if (word1[i] > word2[i])
            return true;  // word1 больше word2
        else if (word1[i] < word2[i])
            return false; // word1 меньше word2
    }
    return false; // Если слова равны, возвращаем false
}

// Сортирует словарь по возрастанию методом пузырька
void SortDict() {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (Compare(dict[j].engl, dict[j + 1].engl))
                swap(dict[j], dict[j + 1]);

    cout << "Словарь успешно отсортирован!" << endl;
}

// Ищет слово в словаре
int Find(char word[], int mode = 2) {
    if (mode == 0) {
        for (int i = 0; i < n; i++)
            if (Equals(dict[i].engl, word))
                return i;
    }
    else if (mode == 1) {
        for (int i = 0; i < n; i++)
            if (Equals(dict[i].rus, word))
                return i;
    }
    else if (mode == 2) {
        for (int i = 0; i < n; i++)
            if (Equals(dict[i].engl, word) || Equals(dict[i].rus, word))
                return i;
    }

    return -1;

}

// Переводит слово
void Translate(int mode) {
    char word[l_word];

    if (mode == 0)
        cout << "Введите слово на английском языке - ";
    else
        cout << "Введите слово на русском языке - ";

    cin >> word;

    int index = Find(word, mode);

    if (index == -1)
        cout << "Слова '" << word << "' нет в словаре!" << endl;
    else
    {
        if (mode == 0)
            cout << "Слово '" << word << "' переводится как '" << dict[index].rus << "'" << endl;
        else
            cout << "Слово '" << word << "' переводится как '" << dict[index].engl << "'" << endl;
    }
}

// Добавляет слово в словарь
void AddWord() {
    char word[l_word], translate[l_word];
    cout << "Введите слово - ";
    cin >> word;

    int index = Find(word);

    if (index == -1)
    {
        cout << "Введите перевод слова '" << word << "' - ";
        cin >> translate;

        strcpy(dict[n].rus, word);
        strcpy(dict[n].engl, translate);

        cout << "Слово " << word << "(" << translate << ") успешно добавлено в словарь!" << endl;
        n++;
        SortDict();
    }
    else
    {
        cout << "Слово '" << word << "' уже находится в словаре!" << endl;
    }

}

// Добавляет слово в словарь
void AddTestWord(const char word[], const char translate[]) {
    strcpy(dict[n].rus, word);
    strcpy(dict[n].engl, translate);
    n++;
}

// Удаляет слово из словаря
void RemoveTestWord(char word[], const char translate[]) {
    int index = Find(word);
    strcpy(dict[index].rus, "");
    strcpy(dict[index].engl, "");
    for (int i = 0; i < 3 - 1; ++i) {
        strcpy(dict[i].rus, dict[i + 1].rus);
        strcpy(dict[i].engl, dict[i + 1].engl);
    }
        strcpy(dict[n - 1].rus, "0");
        strcpy(dict[n - 1].engl, "0");
}

// Переводит слово
void TestTranslate(char word[]) {
    int index = Find(word);
    cout << "Слово '" << word << "' переводится как '" << dict[index].engl << "'" << endl;
}


// Удаляет слово из словаря
void RemoveWord() {
    char word[l_word];
    cout << "Введите слово - ";
    cin >> word;

    int index = Find(word);

    if (index == -1)
        cout << "Слова '" << word << "' нет в словаре!" << endl;
    else
    {
        strcpy(dict[index].rus, "");
        strcpy(dict[index].engl, "");

        for (int i = index; i < n - 1; i++)
        {
            strcpy(dict[i].rus, dict[i + 1].rus);
            strcpy(dict[i].engl, dict[i + 1].engl);
        }

        strcpy(dict[n - 1].rus, "0");
        strcpy(dict[n - 1].engl, "0");

        n--;

        cout << "Cлово " << word << " удалено из словаря!" << endl;
    }

}

// Выводит словарь на экран
void ShowDict() {
    for (int i = 0; i < n; i++)
        if (dict[i].rus[0] != '0')
            cout << i + 1 << ". " << dict[i].rus << " " << dict[i].engl << endl;
    cout << endl;
}

// Печатает словарь в файл
void PrintDict() {
    const char filename[] = "dict.txt";

    ofstream f;
    f.open(filename, ios::binary);

    for (int i = 0; i < n; i++)
        f << dict[i].rus << " " << dict[i].engl << "\n";

    f.close();

    cout << "Словарь напечатан в файл 'dict.txt'" << endl;
}

int interactive() {

    while (true) {
        switch (PrintMenu()) {
            case 1: AddWord();    break;
            case 2: RemoveWord(); break;
            case 3: Translate(0); break;
            case 4: Translate(1); break;
            case 5: ShowDict();   break;
            case 6: PrintDict();  break;
            case 7: return 0;
            default:
                cout << "Надо вводить число от 1 до 7" << endl;
                break;
            }
    }

    return 0;
};

int demo() {
    cout << " ----- Демонстративная версия -----\n\n";
    cout << "По команде 1 в словарь можно добавить пару слов. Пример: собака - dog\n";
    cout << "По команде 2 из словаря можно удалить пару слов.\n";
    cout << "По команде 3 осуществляется перевод с английского на русский.\n";
    cout << "По команде 4 осуществляется перевод с русского на английский.\n";
    cout << "По команде 5 словарь можно вывести на экран.\n";
    cout << "По команде 6 можно сохранить текущий словарь в файл.\n";
    cout << "По команде 7 осуществляется выход из программы.\n\n";

    cout << "Добавим в пустой словарь пару слов: sobaka - dog\n";
    AddTestWord("sobaka", "dog");
    ShowDict();

    cout << "Добавим в словарь пары слов: kot - cat и mashina - car\n";
    AddTestWord("kot", "cat");
    AddTestWord("mashina", "car");
    ShowDict();

    cout << "Удалим пару слов: sobaka - dog\n";
    char* sobakaRemove = strdup("sobaka");
    char* dogRemove = strdup("dog");
    RemoveTestWord(sobakaRemove, dogRemove);
    ShowDict();

    cout << "Переведем слово mashina на английский язык\n";
    char* mashinaTranslate = strdup("mashina");
    TestTranslate(mashinaTranslate);
    cout << endl;

    cout << "Сохраним наш словарь в текстовый файл\n";
    PrintDict();
    return 0;
}

int main(int argc, char *argv[]) {
    bool isInteractive = false;    // по умолчанию демо-режим.

    // Если i передается в качестве аргумента, то программу
    // необходимо запустить в интерактивном режиме
    if ((argc == 2) && strcmp(argv[1], "i") == 0) {
        isInteractive = true;
    }

    if (isInteractive) {
        return interactive();

    } else {
        return demo();
    }
}