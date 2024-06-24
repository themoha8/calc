#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

#define STACK_SIZE 32

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

static double power(double base, int exponent)
{
    double result = 1.0;
    int i;

    for (i = 0; i < abs(exponent); i++)
        result *= base;

    if (exponent < 0)
        result = 1.0 / result;

    return result;
}

int shunting_yard(const char *infix, char *postfix) {
    int i = 0, j = 0, n_par = 0, n_num = 0, n_op = 0;
    char stack[STACK_SIZE];
    int sp = -1;

    while (infix[i] != '\0') {
        char op = infix[i];

        if (op == ' ' || op == '\t' || op == '\n') {
            if (i < EXPRESSION_SIZE)
                i++;
            else {
                fprintf(stderr, "calc: too long expression\n");
                return 0;
            }
            continue;
        }

        if (is_digit(op) || (op == '-' && is_digit(infix[i+1]))) {
            n_num++;
            if (n_op > 1) {
                fprintf(stderr, "calc: Invalid arithmetic expression ([operator operator number] instead of [number operator number])\n");
                return 0;
            } else if (n_op > 0)
                n_op--;
            while ((is_digit(infix[i])) || infix[i] == '-' || infix[i] == '.') {
                postfix[j++] = infix[i++];
                if (infix[i] == '-')
                    break; /* guard from 1--3 */
            }
            postfix[j++] = ' ';
        }
        else if (is_operator(op)) {
            n_op++;
            if (n_num > 1) {
                fprintf(stderr, "calc: Invalid arithmetic expression ([number number operator] instead of [number operator number])\n");
                return 0;
            } else if (n_num > 0)
                n_num--;
            while (sp != -1 && precedence(stack[sp]) >= precedence(op)) {
                postfix[j++] = stack[sp--];
                postfix[j++] = ' ';
            }
            if (sp+1 < STACK_SIZE) {
                stack[++sp] = op;
                if (i < EXPRESSION_SIZE)
                    i++;
                else {
                    fprintf(stderr, "calc: too long expression\n");
                    return 0;
                }
            }
            else {
                fprintf(stderr, "calc: stack full, too many operations\n");
                return 0;
            }
        }
        else if (op == '(') {
            if (infix[i+1] == '*' || infix[i+1] == '/' || infix[i+1] == '%' ||
                infix[i+1] == '^' || infix[i+1] == '+') {
                fprintf(stderr, "calc: invalid expression in parentheses\n");
                return 0;
            }
            n_par++;
            if (sp+1 < STACK_SIZE) {

                if (sp+1 < STACK_SIZE)
                    stack[++sp] = op;
                else {
                    fprintf(stderr, "calc: stack full, too many operations\n");
                    return 0;
                }

                if (i < EXPRESSION_SIZE)
                    i++;
                else {
                    fprintf(stderr, "calc: too long expression\n");
                    return 0;
                }
            }
            else {
                fprintf(stderr, "calc: stack full, too many operations\n");
                return 0;
            }
        }
        else if (op == ')') {
            if (n_op) {
                fprintf(stderr, "calc: invalid expression in parentheses\n");
                return 0;
            }
            if (!n_par) {
                fprintf(stderr, "calc: opening parethesis missing\n");
                return 0;
            }
            n_par--;
            while (sp != -1 && stack[sp] != '(') {
                postfix[j++] = stack[sp--];
                postfix[j++] = ' ';
            }
            if (sp != -1) sp--;

            if (i < EXPRESSION_SIZE)
                i++;
            else {
                fprintf(stderr, "calc: too long expression\n");
                return 0;
            }
        }
        else {
            fprintf(stderr, "calc: error while parsing: '%c'\n", op);
            return 0;
        }
    }

    if (n_op) {
        fprintf(stderr, "calc: too many operators\n");
        return 0;
    } else if (n_num > 1) {
        fprintf(stderr, "calc: too many numbers\n");
        return 0;
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

double evaluate_rpn(char *expression)
{
    double stack[STACK_SIZE];
    int sp = -1;
    char *token = strtok(expression, " ");

    while(token != NULL) {
        if (is_digit(*token) || (is_digit(token[1]) && *token == '-')) {
            stack[++sp] = atof(token);
        }
        else if (is_operator(*token)) {
            double op2 = stack[sp--];
            double op1 = stack[sp--];
            double result = 0;

            switch(*token) {
            case '+':
                result = op1 + op2;
                break;
            case '-':
                result = op1 - op2;
                break;
            case '*':
                result = op1 * op2;
                break;
            case '/':
                result = op1 / op2;
                break;
            case '%':
                result = (int)op1 % (int)op2;
                break;
            case '^':
                result = power(op1, (int)op2);
            }

            stack[++sp] = result;
        }
        token = strtok(NULL, " ");
    }
    return stack[sp];
}
