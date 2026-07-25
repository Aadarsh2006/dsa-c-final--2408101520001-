#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int infixToPostfix(char tokens[][20], int n, char postfix[][20]) {
    char stack[MAX];
    int top = -1;
    int k = 0;

    for (int i = 0; i < n; i++) {

        if (isdigit(tokens[i][0])) {
            strcpy(postfix[k++], tokens[i]);
        }

        else if (tokens[i][0] == '(') {
            stack[++top] = '(';
        }

        else if (tokens[i][0] == ')') {

            while (top != -1 && stack[top] != '(') {
                postfix[k][0] = stack[top--];
                postfix[k][1] = '\0';
                k++;
            }

            if (top == -1)
                return -1;

            top--;
        }

        else if (isOperator(tokens[i][0])) {

            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(tokens[i][0])) {

                postfix[k][0] = stack[top--];
                postfix[k][1] = '\0';
                k++;
            }

            stack[++top] = tokens[i][0];
        }
    }

    while (top != -1) {
        if (stack[top] == '(')
            return -1;

        postfix[k][0] = stack[top--];
        postfix[k][1] = '\0';
        k++;
    }

    return k;
}

int evaluatePostfix(char postfix[][20], int n, int *error) {

    int stack[MAX];
    int top = -1;

    for (int i = 0; i < n; i++) {

        if (isdigit(postfix[i][0])) {
            stack[++top] = atoi(postfix[i]);
        }

        else {

            int b = stack[top--];
            int a = stack[top--];
            int result;

            switch (postfix[i][0]) {

                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    if (b == 0) {
                        *error = 1;
                        return 0;
                    }
                    result = a / b;
                    break;
            }

            stack[++top] = result;
        }
    }

    return stack[top];
}

int main() {

    char line[201];
    char tokens[MAX][20];
    char postfix[MAX][20];

    fgets(line, sizeof(line), stdin);

    int n = 0;

    char *token = strtok(line, " \n");

    while (token != NULL) {
        strcpy(tokens[n++], token);
        token = strtok(NULL, " \n");
    }

    int postfixSize = infixToPostfix(tokens, n, postfix);

    if (postfixSize == -1) {
        printf("ERROR:UNBALANCED");
        return 0;
    }

    int error = 0;

    int ans = evaluatePostfix(postfix, postfixSize, &error);

    if (error)
        printf("ERROR:DIV_BY_ZERO");
    else
        printf("%d", ans);

    return 0;
}