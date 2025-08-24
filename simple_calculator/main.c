#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// custom includes:
#include "stack.h"

// definitions"
#define MAX_CAPACITY 1024;

char *convert_to_rpn(char *buffer);
void solve_rpn(char *rpn);
int solve_operation(int x1, int x2, char operator);


int main(void) {
    char input_buffer[256];
    char cleaned[256];
    cleaned[0] = '\0';

    printf(">>:");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        printf("Input error\n");
        return 1;
    }
    char *token = strtok(input_buffer, " ");
    while (token != NULL) {
        strcat(cleaned, token);
        token = strtok(NULL, " ");
    }

    char *converted = convert_to_rpn(cleaned);
    solve_rpn(converted);
    return 0;
}


void solve_rpn(char *rpn) {
    int len = strlen(rpn);
    Stack solver;
    initialize_stack(&solver);
    for (int i = 0; i < len; i++) {
        if (isspace(rpn[i])) continue;
        if (isdigit(rpn[i])) {
            int temp = rpn[i] - '0';
            while (rpn[i+1] != '\0' && !isspace(rpn[i+1])) {
                temp = temp*10 + (rpn[++i] - '0');
            }
            push(&solver, temp);
        } else if (strchr("+-*/^", rpn[i])) {
            if (rpn[i] == '-' && isdigit(rpn[i+1])) { // rpn[i] == '-' right now, want to look ahead with i+1 to see if the following character is a number and not a space
                int temp = 0; // increment i to be on the number after the minus sign (++i) now need lookahead logic to check that the length has not yet reached the end and that the next character is a number, otherwise add this current temp to the stack
                i++;
                if (i < len && isdigit(rpn[i+1])) {
                    temp = temp*10 + (rpn[i] - '0');
                    i++;
                }
                temp = -temp;
                push(&solver, temp);
                i--;
            }
            int digits[2];
            for (int j = 0; j < 2; j++) {
                digits[j] = pop(&solver);
            }
            int operation = solve_operation(digits[1], digits[0], rpn[i]);
            push(&solver, operation);
        } else {
            printf("Error: Unrecognized operator {%c} :: Caught in solve_rpn()", rpn[i]);
        }
    }
    printf("Solution: %d\n", peek(&solver));
    // print_stack(&solver);
    free(rpn); // this is for after the use of convert_to_rpn() since I allocate memory manually to create a location in heap for the result char array.
}


int solve_operation(int x1, int x2, char operator) {
    switch (operator) {
        case '^': {
            if (x2 == 0) {
                return 1;
            }
            int result = 1;
            for (int i = 0; i < x2; i++) {
                result *= x1;
            }
            return result;
        }
        case '*':
            return x1 * x2;
        case '/':
            return x1 / x2;
        case '+':
            return x1 + x2;
        case '-':
            return x1 - x2;
        default:
            printf("Invalid Operator '%c'", operator);
            return INT_MIN;
    }
}


int precedence(char c) {
    if (c == '^') {
        return 3;
    } else if (c == '/' || c == '*') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else {
        return -1;
    }
}


char *convert_to_rpn(char *buffer) {
    int len = strlen(buffer);
    char *result = malloc(len + 1);
    char stack[len];
    int j = 0;
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = buffer[i];
        // printf("%d: %c\n", i, c);
        if (isdigit(c)) {
            while (i!= len && isdigit(buffer[i])) {
                result[j++] = buffer[i++];
            }
            result[j++] = ' ';
            i--;
        } else if (c == '(') {
            stack[++top] = '(';
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                result[j++] = stack[top--];
            }
            top--;
        } else {
            while (top != -1 && (precedence(c) < precedence(stack[top]) || precedence(c) == precedence(stack[top]))) {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }
    while (top != -1) result[j++] = stack[top--];

    result[j] = '\0';
    printf("RPN: %s\n", result);

    // need to convert this function such that it returns a pointer which points to the result char array.
    return result;
}