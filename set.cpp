#include "header.h"

// Добавление элемента в множество
void setAdd(Set& set, int value) {
    // Проверяем, есть ли элемент в массиве
    for (int i = 0; i < set.size; i++) {
        if (set.data[i] == value) {
            cout << "Элемент " << value << " уже существует в множестве." << endl;
            return;
        }
    }

    // Добавляем элемент, если есть место
    if (set.size < set.capacity) {
        set.data[set.size++] = value;
        cout << "Элемент " << value << " добавлен в множество." << endl;
    } else {
        cout << "Множество переполнено. Добавление невозможно." << endl;
    }
}

// Удаление элемента из множества
void setDel(Set& set, int value) {
    for (int i = 0; i < set.size; i++) {
        if (set.data[i] == value) {
            // Сдвигаем оставшиеся элементы влево
            for (int j = i; j < set.size - 1; j++) {
                set.data[j] = set.data[j + 1];
            }
            set.size--;
            cout << "Элемент " << value << " удалён из множества." << endl;
            return;
        }
    }
    cout << "Элемент " << value << " не найден в множестве." << endl;
}

// Проверка, является ли элемент частью множества
bool setContains(const Set& set, int value) {
    for (int i = 0; i < set.size; i++) {
        if (set.data[i] == value) return true;
    }
    return false;
}

// Вывод множества
void printSet(const Set& set) {
    cout << "Множество: { ";
    for (int i = 0; i < set.size; i++) {
        cout << set.data[i] << " ";
    }
    cout << "}" << endl;
}

// Разбиение множества на два с минимальной разницей сумм (динамическое программирование)
void splitSetWithMinDifference(const Set& set, Set& subset1, Set& subset2) {
    int totalSum = 0;
    for (int i = 0; i < set.size; i++) {
        totalSum += set.data[i];
    }

    int n = set.size;
    int halfSum = totalSum / 2;

    // Инициализация таблицы для динамического программирования
    bool dp[n + 1][halfSum + 1] = {false};
    dp[0][0] = true;

    // Заполняем таблицу
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= halfSum; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= set.data[i - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j - set.data[i - 1]];
            }
        }
    }

    // Находим максимально близкую к halfSum сумму
    int closestSum = 0;
    for (int j = halfSum; j >= 0; j--) {
        if (dp[n][j]) {
            closestSum = j;
            break;
        }
    }

    // Восстанавливаем подмножества
    subset1.size = 0;
    subset2.size = 0;
    int remainingSum = closestSum;
    for (int i = n; i > 0; i--) {
        if (remainingSum >= set.data[i - 1] && dp[i - 1][remainingSum - set.data[i - 1]]) {
            subset1.data[subset1.size++] = set.data[i - 1];
            remainingSum -= set.data[i - 1];
        } else {
            subset2.data[subset2.size++] = set.data[i - 1];
        }
    }

    // Выводим результат
    cout << "Множество 1: { ";
    for (int i = 0; i < subset1.size; i++) {
        cout << subset1.data[i] << " ";
    }
    cout << "}" << endl;

    cout << "Множество 2: { ";
    for (int i = 0; i < subset2.size; i++) {
        cout << subset2.data[i] << " ";
    }
    cout << "}" << endl;

    int subset1Sum = 0, subset2Sum = 0;
    for (int i = 0; i < subset1.size; i++) subset1Sum += subset1.data[i];
    for (int i = 0; i < subset2.size; i++) subset2Sum += subset2.data[i];
    cout << "Разница между суммами: " << abs(subset1Sum - subset2Sum) << endl;
}
