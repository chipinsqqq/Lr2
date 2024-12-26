#include "header.h"

// Создание узла дерева
TreeNode* createNode(int value) {
    TreeNode* newNode = new TreeNode;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Добавление узла в дерево (рекурсивно)
TreeNode* addNode(TreeNode* root, int value) {
    if (root == nullptr) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = addNode(root->left, value);
    } else {
        root->right = addNode(root->right, value);
    }
    return root;
}

// Уровневое чтение "змейкой"
void snakeOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        cout << "Дерево пустое." << endl;
        return;
    }

    // Очередь для уровневого обхода
    Queue queue;
    initQueue(queue);
    enqueue(queue, root);

    bool leftToRight = true; // Флаг для чередования направлений
    string result = "Результат: ";

    while (!isQueueEmpty(queue)) {
        int levelSize = getQueueSize(queue); // Количество узлов на текущем уровне
        int* levelValues = new int[levelSize];
        int index = leftToRight ? 0 : levelSize - 1;

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = dequeue(queue);
            levelValues[index] = node->value;

            if (leftToRight) {
                index++;
            } else {
                index--;
            }

            // Добавляем дочерние узлы в очередь
            if (node->left) enqueue(queue, node->left);
            if (node->right) enqueue(queue, node->right);
        }

        // Формируем строку для текущего уровня
        for (int i = 0; i < levelSize; i++) {
            result += to_string(levelValues[i]);
            if (!(isQueueEmpty(queue) && i == levelSize - 1)) {
                result += " – ";
            }
        }

        delete[] levelValues; // Освобождаем память
        leftToRight = !leftToRight; // Меняем направление
    }

    // Выводим итоговую строку
    cout << result << endl;
}


// Освобождение памяти дерева
void freeTree(TreeNode* root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
