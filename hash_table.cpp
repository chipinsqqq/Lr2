#include "header.h"

void deleteHashTable(HashTable& table) {
    delete[] table.keys;
    delete[] table.values;
    table.keys = nullptr;
    table.values = nullptr;
    table.size = 0;
    table.capacity = 0;
}

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

// Добавление элемента в хеш-таблицу
void hashTableInsert(HashTable& table, const string& key, int value) {
    int index = hashFunction(key, table.capacity);
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

// Рекурсивный подсчёт подчинённых
int countSubordinates(const HashTable& table, const string& manager, int* results, bool* visited) {
    int index = hashFunction(manager, table.capacity);

    // Поиск менеджера в хеш-таблице
    while (table.keys[index] != "" && table.keys[index] != manager) {
        index = (index + 1) % table.capacity;
    }

    // Если менеджер не найден
    if (table.keys[index] == "") {
        return 0;
    }

    // Если уже подсчитан, возвращаем сохранённый результат
    if (visited[index]) {
        return results[index];
    }

    visited[index] = true; // Отмечаем как посещённый

    int total = 0;

    // Проверяем каждого сотрудника
    for (int i = 0; i < table.capacity; i++) {
        if (table.keys[i] != "") {
            int managerIndex = hashTableGet(table, table.keys[i]);

            // Пропускаем случаи, когда сотрудник является своим собственным менеджером
            if (managerIndex == index && table.keys[i] != table.keys[managerIndex]) {
                total += 1 + countSubordinates(table, table.keys[i], results, visited);
            }
        }
    }

    results[index] = total; // Сохраняем результат
    return total;
}

int hashTableGet(const HashTable& table, const string& key) {
    int index = hashFunction(key, table.capacity);
    while (table.keys[index] != "" && table.keys[index] != key) {
        index = (index + 1) % table.capacity;
    }
    return (table.keys[index] == key) ? table.values[index] : -1; // -1, если ключ не найден
}

// Вывод количества подчинённых
void printSubordinateCounts(const HashTable& table) {
    int* results = new int[table.capacity]();
    bool* visited = new bool[table.capacity]();
    for (int i = 0; i < table.capacity; i++) {
        if (table.keys[i] != "") {
            countSubordinates(table, table.keys[i], results, visited);
        }
    }
    for (int i = 0; i < table.capacity; i++) {
        if (table.keys[i] != "") {
            cout << table.keys[i] << ": " << results[i] << endl;
        }
    }
    delete[] results;
    delete[] visited;
}
