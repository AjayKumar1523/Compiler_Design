%{
#include <stdio.h>
%}

%%

"+"  { printf("Recognized operator: +\n"); }
"-"  { printf("Recognized operator: -\n"); }
"*"  { printf("Recognized operator: *\n"); }
"/"  { printf("Recognized operator: /\n"); }

[ \t\n]+      { /* Ignore whitespace */ }
.             { printf("Invalid character: %s\n", yytext); }

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

    return 0;
}

int yywrap() {
    return 1;
}
