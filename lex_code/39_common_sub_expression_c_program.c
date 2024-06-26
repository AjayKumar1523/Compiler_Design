#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CODE_LINES 100
#define MAX_EXPR_LENGTH 50

typedef struct {
    char expression[MAX_EXPR_LENGTH];
    bool evaluated;
} CodeLine;

CodeLine code[MAX_CODE_LINES];
int codeLines = 0;

void optimizeCode() {
    for (int i = 0; i < codeLines; i++) {
        if (!code[i].evaluated) {
            for (int j = i + 1; j < codeLines; j++) {
                if (!code[j].evaluated && strcmp(code[i].expression, code[j].expression) == 0) {
                    printf("Common subexpression found between lines %d and %d\n", i + 1, j + 1);
                    code[j].evaluated = true;
                }
            }
        }
    }
}

void printOptimizedCode() {
    printf("Optimized Code:\n");
    for (int i = 0; i < codeLines; i++) {
        if (!code[i].evaluated) {
            printf("%s\n", code[i].expression);
        }
    }
}

int main() {
    // Example code lines
    strcpy(code[codeLines++].expression, "a = b + c");
    strcpy(code[codeLines++].expression, "d = b + c");
    strcpy(code[codeLines++].expression, "e = a * b");
    strcpy(code[codeLines++].expression, "f = d * c");
    strcpy(code[codeLines++].expression, "g = a * b");

    // Display original code
    printf("Original Code:\n");
    for (int i = 0; i < codeLines; i++) {
        printf("%s\n", code[i].expression);
    }

    // Optimize the code
    optimizeCode();

    // Display optimized code
    printOptimizedCode();

    return 0;
}
