#include <stdio.h>
#include "calculator.h"

int main() {
    char infix[EXPRESSION_SIZE];
    char postfix[EXPRESSION_SIZE];

    printf("Enter infix expression: ");
    fgets(infix, EXPRESSION_SIZE, stdin);

    if (shunting_yard(infix, postfix))
        printf("Postfix expression: %s\n", postfix);

    return 0;
}
