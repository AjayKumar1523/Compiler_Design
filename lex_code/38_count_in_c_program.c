#include <stdio.h>
#include <stdbool.h>

int main() {
    FILE *file;
    char filename[100];
    char ch;
    int characters = 0, words = 0, lines = 0;
    bool inWord = false;

    // Prompt the user to enter the file name
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");

    // Check if the file exists
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        characters++;

        // Check for new lines
        if (ch == '\n') {
            lines++;
        }

        // Check for words
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (inWord) {
                inWord = false;
                words++;
            }
        } else {
            inWord = true;
        }
    }

    // If the file does not end with a space or newline, we should count the last word
    if (inWord) {
        words++;
    }

    // Close the file
    fclose(file);

    // Output the results
    printf("Number of characters: %d\n", characters);
    printf("Number of words: %d\n", words);
    printf("Number of lines: %d\n", lines);

    return 0;
}
