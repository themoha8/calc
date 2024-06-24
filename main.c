#if FOR_WINDOWS
#include <windows.h>
#else
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h> /* free */
#endif
#include <stdio.h>
#include "calculator.h"

static const char logo[] =
"  ____      _            _       _             \n"
" / ___|__ _| | ___ _   _| | __ _| |_ ___  _ __ \n"
"| |   / _` | |/ __| | | | |/ _` | __/ _ \\| '__|\n"
"| |__| (_| | | (__| |_| | | (_| | || (_) | |   \n"
" \\____\\__,_|_|\\___|\\__,_|_|\\__,_|\\__\\___/|_|   \n\n";

static const char welcome[] = "Write a arihmetic expression using "
"'+', '-', '*', '/', '%%' and '^'\nTo exit, press: Ctrl-D for Linux, " 
"Ctrl-C for Windows\nExample: (2 + 3) * 4^3 + 4.5\n\n\n\n";

#if FOR_WINDOWS
static void term_setup(void)
{

    DWORD console_mode;

    /* console setup (enable sequence control) */
    if (!GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &console_mode)) {
        fprintf(stderr, "calc: error console setup in fuction GetConsoleMode\n");
        exit(GetLastError());
    }

    console_mode = console_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), console_mode)) {
        fprintf(stderr, "calc: error console setup in fuction SetConsoleMode\n");
        exit(GetLastError());
    }
}
#endif

int main() {

#if FOR_WINDOWS
    char infix[EXPRESSION_SIZE];
#elif FOR_TESTING
    char infix[EXPRESSION_SIZE];
#else
    char *infix;
#endif
    char postfix[EXPRESSION_SIZE];

#if FOR_WINDOWS
    term_setup();
#endif

    /* set cursor position */
    printf("\x1b[1;1H");
    /* clear screen */
    printf("\x1b[2J");
    /* set font color */
    printf("\x1b[33m");
    printf(logo);
    /* set default font */
    printf("\x1b[0m");
    printf(welcome);
    printf("Enter infix expression: \n");

#if FOR_WINDOWS
    while (fgets(infix, EXPRESSION_SIZE, stdin) != NULL) {
           if (shunting_yard(infix, postfix) && *infix != '\n') {
            double res;
            res = evaluate_rpn(postfix);
            printf("Answer: %g\n\n", res);
        }
        printf("Enter infix expression:\n");
    }
#elif FOR_TESTING
    if(fgets(infix, EXPRESSION_SIZE, stdin))
        if (shunting_yard(infix, postfix) && *infix != '\n') {
            double res;
            res = evaluate_rpn(postfix);
            printf("Answer: %g\n\n", res);
        }
#else
    while ((infix = readline(NULL)) != NULL) {
        if (shunting_yard(infix, postfix) && *infix != '\0') {
            double res;
            res = evaluate_rpn(postfix);
            printf("Answer: %g\n\n", res);
        }
        printf("Enter infix expression: \n");
        free(infix);
    }
#endif

    printf("Bye bye!\n");
    return 0;
}
