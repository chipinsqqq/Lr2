#include "header.h"

// Инициализация хеш-таблицы
void initHashTable(HashTable& table, int capacity) {
    table.capacity = capacity;
    table.size = 0;
    table.keys = new string[capacity];
    table.values = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        table.keys[i] = "";
        table.values[i] = 0;
    }
}

// Хеш-функция
int hashFunction(const string& key, int capacity) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % capacity;
    }
    return hash;
}

// Добавление или обновление элемента в хеш-таблице
void hashTableInsert(HashTable& table, const string& key, int value) {
    int index = hashFunction(key, table.capacity);

    // Линейное пробирование для разрешения коллизий
    while (table.keys[index] != "" && table.keys[index] != key) {
        index = (index + 1) % table.capacity;
    }

    if (table.keys[index] == "") {
        table.keys[index] = key;
        table.values[index] = value;
        table.size++;
    } else {
        table.values[index] += value;
    }
}

// Получение значения из хеш-таблицы
int hashTableGet(const HashTable& table, const string& key) {
    int index = hashFunction(key, table.capacity);

    while (table.keys[index] != "" && table.keys[index] != key) {
        index = (index + 1) % table.capacity;
    }

    if (table.keys[index] == key) {
        return table.values[index];
    }
    return 0; // Если ключ не найден
}

// Вывод содержимого хеш-таблицы
void printHashTable(const HashTable& table) {
    for (int i = 0; i < table.capacity; i++) {
        if (table.keys[i] != "") {
            cout << table.keys[i] << ": " << table.values[i] << endl;
        }
    }
}

// Удаление хеш-таблицы
void deleteHashTable(HashTable& table) {
    delete[] table.keys;
    delete[] table.values;
    table.keys = nullptr;
    table.values = nullptr;
    table.size = 0;
    table.capacity = 0;
}



