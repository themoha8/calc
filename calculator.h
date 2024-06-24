#ifndef CALC_H_SENTRY
#define CALC_H_SENTRY

#define EXPRESSION_SIZE 256

int shunting_yard(const char *infix, char *postfix);
double evaluate_rpn(char *expression);

#endif
