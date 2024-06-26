%{
#include <stdio.h>

int whitespace_count = 0;
int newline_count = 0;
%}

%%

[ \t]+      { whitespace_count += yyleng; }  // Count whitespaces and tabs
\n          { newline_count++; }             // Count newlines

.           { /* Ignore other characters */ }

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);

    printf("Number of whitespaces: %d\n", whitespace_count);
    printf("Number of newline characters: %d\n", newline_count);

    return 0;
}

int yywrap() {
    return 1;
}
