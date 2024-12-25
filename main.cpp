#include "header.h"

// Обработка команд для стека
void Stackcom(Stack& stack, const string& command) {
    if (command.rfind("SPUSH", 0) == 0) {
        string value = command.substr(6); // Извлечение значения после "SPUSH "
        push(stack, value);
    } else if (command == "SPOP") {
        pop(stack);
    } else if (command == "PRINT") {
        printStack(stack);
    } else if (command.rfind("EVAL", 0) == 0) {
        string expression = command.substr(5); // Извлечение выражения после "EVAL "
        string result = LogicalPostfix(expression);
        cout << "Результат выражения: " << result << endl;
    } else {
        cout << "Неизвестная команда: " << command << endl;
    }
}

// Обработка команд для множества
void Setcom(Set& set, const string& command) {
    if (command.rfind("SETADD", 0) == 0) {
        int value = stoi(command.substr(7)); // Извлечение значения после "SETADD "
        setAdd(set, value);
    } else if (command.rfind("SETDEL", 0) == 0) {
        int value = stoi(command.substr(7)); // Извлечение значения после "SETDEL "
        setDel(set, value);
    } else if (command.rfind("SET_AT", 0) == 0) {
        int value = stoi(command.substr(7)); // Извлечение значения после "SET_AT "
        if (setContains(set, value)) {
            cout << "Элемент " << value << " присутствует в множестве." << endl;
        } else {
            cout << "Элемент " << value << " отсутствует в множестве." << endl;
        }
    } else if (command == "PRINT") {
        printSet(set); // Вывод множества
    } else if (command == "SPLIT") {
        Set subset1, subset2;
        splitSetWithMinDifference(set, subset1, subset2); // Разбиение множества
    } else {
        cout << "Неизвестная команда: " << command << endl;
    }
}

// Обработка команд для массива
void Arraycom(SimpleArray& array, const string& command) {
    if (command.rfind("AADD", 0) == 0) {
        int value = stoi(command.substr(5)); // Извлечение значения после "AADD "
        arrayAdd(array, value);
    } else if (command == "PRINT") {
        printArray(array); // Вывод массива
    } else if (command.rfind("ASUM", 0) == 0) {
        int targetSum = stoi(command.substr(5)); // Извлечение целевой суммы после "ASUM "
        findSubarraysWithSum(array, targetSum);
    } else {
        cout << "Неизвестная команда: " << command << endl;
    }
}

// Обработка команд для дерева
void Treecom(TreeNode*& root, const string& command) {
    if (command.rfind("TADD", 0) == 0) {
        int value = stoi(command.substr(5)); // Извлечение значения после "TADD "
        root = addNode(root, value);
        cout << "Элемент " << value << " добавлен в дерево." << endl;
    } else if (command == "PRINT") {
        cout << "Чтение дерева змейкой:" << endl;
        snakeOrderTraversal(root); // Уровневый обход дерева "змейкой"
    } else if (command == "FREE") {
        freeTree(root);
        root = nullptr;
        cout << "Дерево освобождено." << endl;
    } else {
        cout << "Неизвестная команда: " << command << endl;
    }
}

// Обработка команд для хеш-таблицы
void HashTablecom(HashTable& table, const string& command) {
    if (command.rfind("HADD", 0) == 0) {
        size_t spacePos = command.find(' ', 5); // Позиция пробела после ключа
        string employee = command.substr(5, spacePos - 5); // Извлечение сотрудника
        string manager = command.substr(spacePos + 1);     // Извлечение менеджера

        // Добавляем сотрудника и менеджера в иерархию
        hashTableInsert(table, manager, 1); // Менеджеру добавляем одного подчинённого
        hashTableInsert(table, employee, 0); // Убедимся, что сотрудник добавлен с 0 подчинёнными
        cout << "Сотрудник \"" << employee << "\" добавлен с менеджером \"" << manager << "\"." << endl;
    } else if (command == "PRINT") {
        cout << "Содержимое хеш-таблицы:" << endl;
        printHashTable(table);
    } else {
        cout << "Неизвестная команда: " << command << endl;
    }
}

// Главная функция
int main() {
    Set mySet;                // Инициализация множества
    Stack myStack = {nullptr}; // Инициализация стека
    SimpleArray myArray;      // Инициализация массива
    TreeNode* myTree = nullptr; // Инициализация дерева
    HashTable hashTable;
    initHashTable(hashTable, 20); // Инициализация хеш-таблицы с вместимостью 20

    cout << "Введите команду. Для выхода введите EXIT." << endl;
    string command;
    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command == "EXIT") {
            break;
        } else if (command[0] == 'E') { 
            Setcom(mySet, command.substr(2)); // Команды для множества
        } else if (command[0] == 'S') { 
            Stackcom(myStack, command.substr(2)); // Команды для стека
        } else if (command[0] == 'A') { 
            Arraycom(myArray, command.substr(2)); // Команды для массива
        } else if (command[0] == 'T') {
            Treecom(myTree, command.substr(2)); // Команды для дерева
        } else if (command[0] == 'H') {
            HashTablecom(hashTable, command.substr(2)); // Команды для хеш-таблицы
        } else {
            cout << "Неизвестная команда или структура данных. Попробуйте снова." << endl;
        }
    }

    // Освобождаем дерево и хеш-таблицу перед завершением программы
    freeTree(myTree);
    deleteHashTable(hashTable);

    return 0;
}
