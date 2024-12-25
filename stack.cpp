#include "header.h"

// Добавление элемента в стек
void push(Stack& stack, const string& value) {
    StackNode* newNode = new StackNode{value, stack.top};
    stack.top = newNode;
}

// Удаление элемента из стека
void pop(Stack& stack) {
    if (stack.top == nullptr) {
        return;
    }
    StackNode* temp = stack.top;
    stack.top = stack.top->next;
    delete temp;
}

// Определение приоритета оператора
int precedence(const string& op) {
    if (op == "!") return 3;
    if (op == "&") return 2;
    if (op == "|" || op == "^") return 1;
    return 0;
}

void printStack(const Stack& stack) {
    if (stack.top == nullptr) {
        cout << "Стек пуст!" << endl;
        return;
    }

    cout << "Содержимое стека: ";
    StackNode* current = stack.top;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;
}


// Преобразование инфиксного выражения в постфиксное
string infixToPostfix(const string& expression) {
    string postfix;
    Stack operatorStack;
    operatorStack.top = nullptr;

    for (char ch : expression) {
        string token(1, ch);

        if (token == "0" || token == "1") {
            postfix += token;
        } else if (token == "(") {
            push(operatorStack, token);
        } else if (token == ")") {
            while (operatorStack.top != nullptr && operatorStack.top->value != "(") {
                postfix += operatorStack.top->value;
                pop(operatorStack);
            }
            pop(operatorStack); // Удаляем открывающую скобку
        } else {
            while (operatorStack.top != nullptr &&
                   precedence(operatorStack.top->value) >= precedence(token)) {
                postfix += operatorStack.top->value;
                pop(operatorStack);
            }
            push(operatorStack, token);
        }
    }

    while (operatorStack.top != nullptr) {
        postfix += operatorStack.top->value;
        pop(operatorStack);
    }

    return postfix;
}

// Вычисление постфиксного выражения
string evaluatePostfix(const string& expression) {
    Stack valueStack;
    valueStack.top = nullptr;

    for (char ch : expression) {
        string token(1, ch);

        if (token == "0" || token == "1") {
            push(valueStack, token);
        } else if (token == "!") {
            string val = valueStack.top->value;
            pop(valueStack);
            push(valueStack, val == "1" ? "0" : "1");
        } else if (token == "&" || token == "|" || token == "^") {
            string val2 = valueStack.top->value;
            pop(valueStack);
            string val1 = valueStack.top->value;
            pop(valueStack);

            int result = 0;
            if (token == "&") {
                result = (val1 == "1" && val2 == "1") ? 1 : 0;
            } else if (token == "|") {
                result = (val1 == "1" || val2 == "1") ? 1 : 0;
            } else if (token == "^") {
                result = (val1 == "1") ^ (val2 == "1");
            }

            push(valueStack, result ? "1" : "0");
        }
    }

    return valueStack.top->value;
}

// Главная функция для обработки логического выражения
string LogicalPostfix(const string& expression) {
    string postfix = infixToPostfix(expression);
    return evaluatePostfix(postfix);
}
