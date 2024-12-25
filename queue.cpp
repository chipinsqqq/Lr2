#include "header.h"

// Инициализация очереди
void initQueue(Queue& queue) {
    queue.front = nullptr;
    queue.rear = nullptr;
}

// Добавление элемента в очередь
void enqueue(Queue& queue, TreeNode* value) {
    QueueNode* newNode = new QueueNode;
    newNode->data = value;
    newNode->next = nullptr;
    if (queue.rear == nullptr) {
        queue.front = queue.rear = newNode;
        return;
    }
    queue.rear->next = newNode;
    queue.rear = newNode;
}

// Удаление элемента из очереди
TreeNode* dequeue(Queue& queue) {
    if (queue.front == nullptr) return nullptr;

    QueueNode* temp = queue.front;
    TreeNode* data = temp->data;
    queue.front = queue.front->next;

    if (queue.front == nullptr) {
        queue.rear = nullptr;
    }

    delete temp;
    return data;
}

// Проверка, пуста ли очередь
bool isQueueEmpty(const Queue& queue) {
    return queue.front == nullptr;
}

// Получение размера очереди
int getQueueSize(const Queue& queue) {
    int size = 0;
    QueueNode* current = queue.front;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}
