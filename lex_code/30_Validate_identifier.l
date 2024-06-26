%{
#include <stdio.h>
#include <ctype.h>

%}

/* Rules Section */
%%

[_a-zA-Z][_a-zA-Z0-9]*  { printf("Valid identifier: %s\n", yytext); }
[ \t\n]+                { /* Ignore whitespace */ }
.                       { printf("Invalid identifier: %s\n", yytext); }

%%

/* Main Function */
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Could not open file %s\n", argv[1]);
        return 1;
    }

    yylex();
    fclose(yyin);

    return 0;
}

int yywrap() {
    return 1;
}
