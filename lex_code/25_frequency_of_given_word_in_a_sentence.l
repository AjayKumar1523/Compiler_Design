%{
#include <stdio.h>
#include <string.h>

char search_word[100];
int word_count = 0;

void count_word(char *text) {
    if (strcmp(text, search_word) == 0) {
        word_count++;
    }
}
%}

%%
[a-zA-Z]+ { count_word(yytext); } // Match words
.|\n      ;  // Ignore any other character
%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <word_to_search>\n", argv[0]);
        return 1;
    }

    strcpy(search_word, argv[1]);

    printf("Enter a sentence: ");
    yylex();

    printf("Frequency of '%s': %d\n", search_word, word_count);
    return 0;
}

int yywrap() {
    return 1;
}
