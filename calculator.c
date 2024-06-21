#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

#define STACK_SIZE 64

static inline int is_digit(int op)
{
    return (op >= '0' && op <= '9');
}

static inline int is_operator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' ||
            op == '^');
}

static int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

int shunting_yard(const char *infix, char *postfix) {
    int i = 0, j = 0, count = 0;
    char stack[STACK_SIZE];
    int sp = -1;

    while (infix[i] != '\0') {
        char op = infix[i];

        if (op == ' ' || op == '\t' || op == '\n') {
            i++;
            continue;
        }

        if (is_digit(op) || (op == '-' && is_digit(infix[i+1]))) {
            while ((is_digit(infix[i])) || infix[i] == '-' || infix[i] == '.') {
                postfix[j++] = infix[i++];
                if (infix[i] == '-')
                    break; /* guard from 1--3 */
            }
            postfix[j++] = ' ';
        }
        else if (is_operator(op)) {
            while (sp != -1 && precedence(stack[sp]) >= precedence(op)) {
                postfix[j++] = stack[sp--];
                postfix[j++] = ' ';
            }
            if (sp+1 < STACK_SIZE) {
                stack[++sp] = op;
                i++;
            }
            else {
                fprintf(stderr, "calc: stack full, too many operations\n");
                return 0;
            }
        }
        else if (op == '(') {
            count++;
            if (sp+1 < STACK_SIZE) {
                stack[++sp] = op;
                i++;
            }
            else {
                fprintf(stderr, "calc: stack full, too many operations\n");
                return 0;
            }
        }
        else if (op == ')') {
            if (!count) {
                fprintf(stderr, "calc: opening parethesis missing\n");
                return 0;
            }
            count--;
            while (sp != -1 && stack[sp] != '(') {
                postfix[j++] = stack[sp--];
                postfix[j++] = ' ';
            }
            if (sp != -1) sp--;
            i++;
        }
        else {
            fprintf(stderr, "calc: error while parsing: '%c'\n", op);
            return 0;
        }
    }

    while (sp != -1) {
        if (stack[sp] == '(') {
            fprintf(stderr, "calc: closing parethesis missing\n");
            return 0;
        }
        postfix[j++] = stack[sp--];
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
    return 1;
}
