#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char op[3];
    char arg1[MAX];
    char arg2[MAX];
    char result[MAX];
} TAC;

int tempVarCount = 0;
TAC tac[MAX];
int tacCount = 0;

char* newTemp() {
    char *temp = (char *)malloc(MAX * sizeof(char));
    sprintf(temp, "t%d", tempVarCount++);
    return temp;
}

void generateTAC(char *op, char *arg1, char *arg2, char *result) {
    strcpy(tac[tacCount].op, op);
    strcpy(tac[tacCount].arg1, arg1);
    strcpy(tac[tacCount].arg2, arg2);
    strcpy(tac[tacCount].result, result);
    tacCount++;
}

char* parseExpression(char **exp);

char* parseFactor(char **exp) {
    while (isspace(**exp)) (*exp)++;
    if (**exp == '(') {
        (*exp)++;
        char *result = parseExpression(exp);
        while (isspace(**exp)) (*exp)++;
        if (**exp == ')') {
            (*exp)++;
        }
        return result;
    } else if (isdigit(**exp) || isalpha(**exp)) {
        char *num = (char *)malloc(MAX * sizeof(char));
        int i = 0;
        while (isdigit(**exp) || isalpha(**exp)) {
            num[i++] = **exp;
            (*exp)++;
        }
        num[i] = '\0';
        return num;
    }
    return NULL;
}

char* parseTerm(char **exp) {
    char *arg1 = parseFactor(exp);
    while (isspace(**exp)) (*exp)++;
    while (**exp == '*' || **exp == '/') {
        char op = **exp;
        (*exp)++;
        char *arg2 = parseFactor(exp);
        char *result = newTemp();
        char opStr[2] = { op, '\0' };
        generateTAC(opStr, arg1, arg2, result);
        arg1 = result;
        while (isspace(**exp)) (*exp)++;
    }
    return arg1;
}

char* parseExpression(char **exp) {
    char *arg1 = parseTerm(exp);
    while (isspace(**exp)) (*exp)++;
    while (**exp == '+' || **exp == '-') {
        char op = **exp;
        (*exp)++;
        char *arg2 = parseTerm(exp);
        char *result = newTemp();
        char opStr[2] = { op, '\0' };
        generateTAC(opStr, arg1, arg2, result);
        arg1 = result;
        while (isspace(**exp)) (*exp)++;
    }
    return arg1;
}

void printTAC() {
    printf("Three Address Code:\n");
    for (int i = 0; i < tacCount; i++) {
        if (strcmp(tac[i].arg2, "") == 0) {
            printf("%s = %s %s\n", tac[i].result, tac[i].op, tac[i].arg1);
        } else {
            printf("%s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);
        }
    }
}

int main() {
    char expression[MAX];
    printf("Enter an expression: ");
    scanf("%[^\n]s", expression);

    char *expPtr = expression;
    parseExpression(&expPtr);

    printTAC();

    return 0;
}
