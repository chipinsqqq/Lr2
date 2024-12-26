#include "header.h"

Set::Set(int cap) : capacity(cap), size(0) {
    keys = new std::string[capacity];
    for (int i = 0; i < capacity; ++i) {
        keys[i] = "";
    }
}

Set::~Set() {
    delete[] keys;
}

// Реализация функций для работы с множеством
void setAdd(Set& set, int value) {
    string key = to_string(value);
    int index = hashFunction(key, set.capacity);

    // Линейное пробирование для разрешения коллизий
    while (set.keys[index] != "" && set.keys[index] != key) {
        index = (index + 1) % set.capacity;
    }

    if (set.keys[index] == "") {
        set.keys[index] = key;
        set.size++;
        cout << "Элемент " << value << " добавлен в множество." << endl;
    } else {
        cout << "Элемент " << value << " уже существует в множестве." << endl;
    }
}

void setDel(Set& set, int value) {
    string key = to_string(value);
    int index = hashFunction(key, set.capacity);

    while (set.keys[index] != "" && set.keys[index] != key) {
        index = (index + 1) % set.capacity;
    }

    if (set.keys[index] == key) {
        set.keys[index] = "";
        set.size--;
        cout << "Элемент " << value << " удалён из множества." << endl;
    } else {
        cout << "Элемент " << value << " не найден в множестве." << endl;
    }
}

bool setContains(const Set& set, int value) {
    string key = to_string(value);
    int index = hashFunction(key, set.capacity);

    while (set.keys[index] != "" && set.keys[index] != key) {
        index = (index + 1) % set.capacity;
    }

    return set.keys[index] == key;
}

void printSet(const Set& set) {
    cout << "Множество: { ";
    for (int i = 0; i < set.capacity; i++) {
        if (!set.keys[i].empty()) {
            cout << set.keys[i] << " ";
        }
    }
    cout << "}" << endl;
}

// Разбиение множества на два подмножества с минимальной разницей сумм
void splitSetWithMinDifference(const Set& set, Set& subset1, Set& subset2) {
    int elements[set.size];
    int elementCount = 0;

    // Собираем все элементы множества
    for (int i = 0; i < set.capacity; i++) {
        if (!set.keys[i].empty()) {
            elements[elementCount++] = stoi(set.keys[i]);
        }
    }

    int totalSum = 0;
    for (int i = 0; i < elementCount; i++) {
        totalSum += elements[i];
    }

    int n = elementCount;
    int halfSum = totalSum / 2;

    // Динамическое программирование для минимизации разницы сумм
    bool** dp = new bool*[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = new bool[halfSum + 1]();
    }
    dp[0][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= halfSum; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= elements[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - elements[i - 1]];
            }
        }
    }

    int closestSum = 0;
    for (int j = halfSum; j >= 0; j--) {
        if (dp[n][j]) {
            closestSum = j;
            break;
        }
    }

    subset1.size = 0;
    subset2.size = 0;
    int remainingSum = closestSum;

    for (int i = n; i > 0; i--) {
        if (remainingSum >= elements[i - 1] && dp[i - 1][remainingSum - elements[i - 1]]) {
            setAdd(subset1, elements[i - 1]);
            remainingSum -= elements[i - 1];
        } else {
            setAdd(subset2, elements[i - 1]);
        }
    }

    for (int i = 0; i <= n; i++) {
        delete[] dp[i];
    }
    delete[] dp;

    // Выводим результат
    cout << "Множество 1: ";
    printSet(subset1);

    cout << "Множество 2: ";
    printSet(subset2);

    cout << "Разница между суммами: " << abs(totalSum - 2 * closestSum) << endl;
}
