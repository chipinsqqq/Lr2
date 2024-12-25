#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// Узел стека
struct StackNode {
    string value;
    StackNode* next;
};

// Стек
struct Stack {
    StackNode* top; // Указатель на вершину стека
};

// Функции для работы со стеком
void push(Stack& stack, const string& value);
void pop(Stack& stack);
void printStack(const Stack& stack);

// Логические операции
int precedence(const string& op);
string infixToPostfix(const string& expression);
string evaluatePostfix(const string& expression);
string LogicalPostfix(const string& expression);

struct Set {
    int data[100]; // Массив фиксированного размера
    int size;      // Текущий размер множества
    int capacity;  // Вместимость множества

    Set() : size(0), capacity(100) {} // Конструктор для инициализации множества
};

// Функции для работы с множеством
void setAdd(Set& set, int value); // Добавление элемента в множество
void setDel(Set& set, int value); // Удаление элемента из множества
bool setContains(const Set& set, int value); // Проверка наличия элемента в множестве
void printSet(const Set& set); // Вывод множества
void splitSetWithMinDifference(const Set& set, Set& subset1, Set& subset2); // Разбиение множества

// Структура для массива
struct SimpleArray {
    int data[100]; // Массив фиксированного размера
    int size;      // Текущий размер массива
    int capacity;  // Вместимость массива

    SimpleArray() : size(0), capacity(100) {} // Конструктор для инициализации массива
};

// Функции для работы с массивом
void arrayAdd(SimpleArray& array, int value); // Добавление элемента
void printArray(const SimpleArray& array);   // Вывод массива
void findSubarraysWithSum(const SimpleArray& array, int targetSum); // Поиск подмассивов с суммой

// Узел двоичного дерева
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
};

// Очередь для уровневого обхода
struct QueueNode {
    TreeNode* data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
};

// Функции работы с деревом
TreeNode* createNode(int value);
TreeNode* addNode(TreeNode* root, int value);
void snakeOrderTraversal(TreeNode* root);
void freeTree(TreeNode* root);

// Функции работы с очередью
void initQueue(Queue& queue);
void enqueue(Queue& queue, TreeNode* value);
TreeNode* dequeue(Queue& queue);
bool isQueueEmpty(const Queue& queue);
int getQueueSize(const Queue& queue);

// Структура для хеш-таблицы
struct HashTable {
    string* keys;   // Массив ключей
    int* values;    // Массив значений
    int capacity;   // Вместимость таблицы
    int size;       // Текущий размер таблицы
};

// Инициализация хеш-таблицы
void initHashTable(HashTable& table, int capacity);
// Хеш-функция
int hashFunction(const string& key, int capacity);
// Добавление или обновление элемента в хеш-таблице
void hashTableInsert(HashTable& table, const string& key, int value);
// Получение значения из хеш-таблицы
int hashTableGet(const HashTable& table, const string& key);
// Вывод содержимого хеш-таблицы
void printHashTable(const HashTable& table);
// Удаление хеш-таблицы
void deleteHashTable(HashTable& table);
