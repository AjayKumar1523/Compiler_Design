%{
#include <stdio.h>
#include <stdlib.h>

int const_count = 0;
extern FILE *yyin;
%}

%%

[0-9]+("u"|"U"|"l"|"L"|"ul"|"UL"|"lu"|"LU")? { const_count++; }      
[0-9]+\.[0-9]+([eE][-+]?[0-9]+)?("f"|"F"|"l"|"L")? { const_count++; } 
\'([^\\\n]|(\\.))?\' { const_count++; }                          
\"([^\\\n]|(\\.))*\" { const_count++; }                           

%%

int yywrap() {
    return 1;
}

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

    printf("Constants: %d\n", const_count);

    return 0;
}