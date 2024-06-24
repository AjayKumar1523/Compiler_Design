%{
#include <stdio.h>
int macro_count = 0;
int header_count = 0;
%}

%%

"/"([^]|\+[^/])\+"/"    { /* ignore multi-line comments */ }
"//".*                        { /* ignore single-line comments */ }

"#include"                    { header_count++; }
"#define"                    { macro_count++; }

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

    printf("Macros defined: %d\n", macro_count);
    printf("Header files included: %d\n", header_count);

    return 0;
}

int yywrap() {
    return 1;
}
