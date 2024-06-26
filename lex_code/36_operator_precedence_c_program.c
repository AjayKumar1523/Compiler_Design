#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Function prototypes
double parseExpression(const char** str);
double parseTerm(const char** str);
double parseFactor(const char** str);
double parseNumber(const char** str);

// Function to parse an expression (handles + and -)
double parseExpression(const char** str) {
    double result = parseTerm(str);
    while (**str == '+' || **str == '-') {
        char op = **str;
        (*str)++;
        if (op == '+') {
            result += parseTerm(str);
        } else {
            result -= parseTerm(str);
        }
    }
    return result;
}

// Function to parse a term (handles * and /)
double parseTerm(const char** str) {
    double result = parseFactor(str);
    while (**str == '*' || **str == '/') {
        char op = **str;
        (*str)++;
        if (op == '*') {
            result *= parseFactor(str);
        } else {
            result /= parseFactor(str);
        }
    }
    return result;
}

// Function to parse a factor (handles parentheses and exponentiation)
double parseFactor(const char** str) {
    double result;
    if (**str == '(') {
        (*str)++;
        result = parseExpression(str);
        if (**str == ')') {
            (*str)++;
        } else {
            printf("Error: Mismatched parentheses\n");
            exit(1);
        }
    } else {
        result = parseNumber(str);
    }

    // Handle exponentiation
    while (**str == '^') {
        (*str)++;
        result = pow(result, parseFactor(str));
    }

    return result;
}

// Function to parse a number
double parseNumber(const char** str) {
    double result = 0.0;
    while (isdigit(**str)) {
        result = result * 10 + (**str - '0');
        (*str)++;
    }
    if (**str == '.') {
        (*str)++;
        double fraction = 1.0;
        while (isdigit(**str)) {
            fraction /= 10;
            result += (**str - '0') * fraction;
            (*str)++;
        }
    }
    return result;
}

// Main function to test the parser
int main() {
    char input[100];
    printf("Enter an expression: ");
    scanf("%s", input);

    const char* str = input;
    double result = parseExpression(&str);
    if (*str == '\0') {
        printf("The result is: %lf\n", result);
    } else {
        printf("Error: Invalid expression\n");
    }

    return 0;
}
