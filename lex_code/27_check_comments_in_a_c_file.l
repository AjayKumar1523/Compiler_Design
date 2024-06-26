%{
#include <stdio.h>

int line_number = 1;

void check_comment(char *text, int type) {
    if (type == 1) {
        printf("Line %d: Single-line comment\n", line_number);
    } else if (type == 2) {
        printf("Line %d: Multi-line comment\n", line_number);
    }
}
%}

%%

"//".*               { check_comment(yytext, 1); }
"/*"([^*]|\*+[^*/])*\*+"/" { check_comment(yytext, 2); }

\n                  { line_number++; }
.                   { /* ignore other characters */ }
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
