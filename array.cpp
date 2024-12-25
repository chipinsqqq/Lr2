#include "header.h"

// Добавление элемента в массив
void arrayAdd(SimpleArray& array, int value) {
    if (array.size < array.capacity) {
        array.data[array.size++] = value;
        cout << "Элемент " << value << " добавлен в массив." << endl;
    } else {
        cout << "Массив переполнен. Добавление невозможно." << endl;
    }
}

// Вывод содержимого массива
void printArray(const SimpleArray& array) {
    cout << "Массив: [ ";
    for (int i = 0; i < array.size; i++) {
        cout << array.data[i] << " ";
    }
    cout << "]" << endl;
}

// Нахождение всех подмассивов, сумма которых равна заданному числу
void findSubarraysWithSum(const SimpleArray& array, int targetSum) {
    bool found = false;
    cout << "Подмассивы с суммой " << targetSum << ":" << endl;

    for (int start = 0; start < array.size; start++) {
        int currentSum = 0;
        for (int end = start; end < array.size; end++) {
            currentSum += array.data[end];
            if (currentSum == targetSum) {
                found = true;
                cout << "[ ";
                for (int i = start; i <= end; i++) {
                    cout << array.data[i] << " ";
                }
                cout << "]" << endl;
            }
        }
    }

    if (!found) {
        cout << "Нет подмассивов с суммой " << targetSum << "." << endl;
    }
}
