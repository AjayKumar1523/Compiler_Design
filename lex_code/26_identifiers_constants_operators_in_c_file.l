%{
#include <stdio.h>
#include <ctype.h>

int identifiers = 0;
int constants = 0;
int operators = 0;

void count_identifier(char *text) {
    identifiers++;
    printf("Identifier: %s\n", text);
}

void count_constant(char *text) {
    constants++;
    printf("Constant: %s\n", text);
}

void count_operator(char *text) {
    operators++;
    printf("Operator: %s\n", text);
}

%}

%%

"/*"([^*]|\*+[^*/])*\*+"/"        { /* ignore multi-line comments */ }
"//".*                            { /* ignore single-line comments */ }

[ \t\n]+                          { /* ignore spaces, tabs, and new lines */ }

[a-zA-Z_][a-zA-Z0-9_]*            { count_identifier(yytext); }
[0-9]+                            { count_constant(yytext); }
"+"|"-"|"*"|"/"|"="|"<"|">"        { count_operator(yytext); }

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

    printf("Identifiers: %d\n", identifiers);
    printf("Constants: %d\n", constants);
    printf("Operators: %d\n", operators);

    return 0;
}

int yywrap() {
    return 1;
}
