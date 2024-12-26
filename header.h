#include <iostream>
#include <string>
using namespace std;

// Узел стека
struct StackNode {
    string value;
    StackNode* next;
};

// Стек
struct Stack {
    StackNode* top;
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

// Структура множества
struct Set {
    string* keys;
    int capacity;
    int size;

    Set(int cap); // Конструктор
    ~Set();       // Деструктор
};

// Функции для работы с множеством
void setAdd(Set& set, int value);
void setDel(Set& set, int value);
bool setContains(const Set& set, int value);
void printSet(const Set& set);
void splitSetWithMinDifference(const Set& set, Set& subset1, Set& subset2);

// Структура для массива
struct SimpleArray {
    int data[100];
    int size;
    int capacity;

    SimpleArray();
};

// Функции для работы с массивом
void arrayAdd(SimpleArray& array, int value);
void printArray(const SimpleArray& array);
void findSubarraysWithSum(const SimpleArray& array, int targetSum);

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

    HashTable() : keys(nullptr), values(nullptr), capacity(0), size(0) {}
    HashTable(int cap) : capacity(cap), size(0) {
        keys = new string[capacity];
        values = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            keys[i] = "";
            values[i] = 0;
        }
    }
    ~HashTable() {
        delete[] keys;
        delete[] values;
    }
};

// Функции для работы с хеш-таблицей
void deleteHashTable(HashTable& table);
void initHashTable(HashTable& table, int capacity);
int hashFunction(const string& key, int capacity);
void hashTableInsert(HashTable& table, const string& key, int value);
int hashTableGet(const HashTable& table, const string& key); // Определите, если потребуется
int hashTableGet(const HashTable& table, const string& key);

// Функции для подсчёта подчинённых
int countSubordinates(const HashTable& table, const string& manager, int* results, bool* visited);
void printSubordinateCounts(const HashTable& table);
