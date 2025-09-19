#include <stdio.h>
#define MAX 8

int stack[MAX];
int top = -1;

int isFull() {
    return top == MAX - 1;
}

int isEmpty() {
    return top == -1;
}

void display() {
    if (isEmpty()) {
        printf("Stack is empty\n\n");
        return;
    }
    printf("Stack state:\n");
    for (int i = top; i >= 0; i--) {
        printf("| %d |\n", stack[i]);
    }
    printf("-----\n\n");
}

void push(int val) {
    if (!isFull()) {
        stack[++top] = val;
        printf("PUSH %d\n", val);
        display();
    }
}

int pop() {
    if (!isEmpty()) {
        int x = stack[top--];
        printf("POP %d\n", x);
        display();
        return x;
    }
    return -1;
}

int main() {
    push(10);
    push(20);
    pop();
    push(25);
    push(50);
    push(70);
    pop();
    pop();
    push(100);
    pop();
    return 0;
}
