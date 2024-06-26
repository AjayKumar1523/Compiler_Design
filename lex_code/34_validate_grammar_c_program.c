#include <stdio.h>
#include <string.h>

// Function to check if the string matches the grammar S -> aSb | ab
int checkGrammar(const char* str, int start, int end) {
    if (start > end) {
        return 0;  // Invalid case
    }
    if (start == end - 1 && str[start] == 'a' && str[end] == 'b') {
        return 1;  // Match the rule S -> ab
    }
    if (str[start] == 'a' && str[end] == 'b') {
        return checkGrammar(str, start + 1, end - 1);  // Match the rule S -> aSb
    }
    return 0;  // No match
}

int main() {
    char input[100];
    printf("Enter a string: ");
    scanf("%s", input);
    
    int length = strlen(input);
    if (checkGrammar(input, 0, length - 1)) {
        printf("The string satisfies the grammar.\n");
    } else {
        printf("The string does not satisfy the grammar.\n");
    }
    
    return 0;
}
