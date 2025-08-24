//
// Created by user on 2025-08-21.
//

#ifndef STACK_H
#define STACK_H

enum { MAX_SIZE = 100 };

typedef struct {
    int arr[MAX_SIZE];
    int top;
    int size;
} Stack;

void initialize_stack(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);
void print_stack(Stack *stack);

#endif //STACK_H