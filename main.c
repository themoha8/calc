#if FOR_WINDOWS
#include <windows.h>
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
"'+', '-', '*', '/', '%%' and '^'\nExample: (2 + 3) * 4^3\n\n\n\n";

int main() {

    char infix[EXPRESSION_SIZE];
    char postfix[EXPRESSION_SIZE];

#if FOR_WINDOWS
    DWORD console_mode;

    /* console setup (enable sequence control) */
    if (!GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &console_mode)) {
        fprinf("calc: error console setup in fuction GetConsoleMode\n");
        return GetLastError();
    }

    console_mode = console_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), console_mode)) {
        fprinf("calc: error console setup in fuction SetConsoleMode\n");
        return GetLastError();
    }
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

    printf("Enter infix expression: ");
    fgets(infix, EXPRESSION_SIZE, stdin);

    if (shunting_yard(infix, postfix))
        printf("Postfix expression: %s\n", postfix);

    return 0;
}
