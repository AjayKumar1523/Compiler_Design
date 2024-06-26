#include <stdio.h>
#include <string.h>

// Function prototypes
int S(const char* str, int* index);

// Function to parse S -> aSb | ab
int S(const char* str, int* index) {
    int start_index = *index;

    if (str[*index] == 'a') {
        (*index)++;
        if (S(str, index)) {
            if (str[*index] == 'b') {
                (*index)++;
                return 1;
            }
        }
        *index = start_index;  // Backtrack
    }

    if (str[*index] == 'a') {
        (*index)++;
        if (str[*index] == 'b') {
            (*index)++;
            return 1;
        }
    }

    *index = start_index;  // Backtrack
    return 0;
}

// Main function to test the recursive descent parser
int main() {
    char input[100];
    printf("Enter a string: ");
    scanf("%s", input);

    int index = 0;
    if (S(input, &index) && input[index] == '\0') {
        printf("The string satisfies the grammar.\n");
    } else {
        printf("The string does not satisfy the grammar.\n");
    }

    return 0;
}
