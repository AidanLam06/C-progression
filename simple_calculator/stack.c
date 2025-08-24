//
// Created by user on 2025-08-21.
//
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

void initialize_stack(Stack *stack) {
    stack->top = -1;
    stack->size = 0;
}

bool isEmpty(Stack *stack) {
    return stack->top == -1;
}

bool isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
    stack->size++;
    // printf("Pushed %d onto the stack\n", value);
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    int popped = stack->arr[stack->top];
    stack->top--;
    stack->size--;
    // printf("Popped %d from the stack\n", popped);
    return popped;
}

int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->arr[stack->top];
}

void print_stack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    // printf("Stack top is %d holding %d elements:", stack->top, stack->size);
    for (int i = 0; i <= stack->top; i++) {
        if (i>0) printf("->");
        printf("%d",stack->arr[i]);
    }
    printf("\n");
}