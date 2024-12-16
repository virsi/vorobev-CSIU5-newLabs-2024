#pragma once

namespace {
const int max_size = 100;
const int l_word = 31;
struct Dictionary {
    char engl[l_word];	// слово по-английски
    char rus[l_word];	// слово по-русски
};

Dictionary dict[max_size];	// массив структур для хранения словаря в оперативной памяти
int n = 0;	
}