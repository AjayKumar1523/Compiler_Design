%{
#include <stdio.h>

int tag_count = 0;

void print_tag(const char *tag) {
    printf("HTML Tag: %s\n", tag);
    tag_count++;
}

%}

%%

"<"[^>]*>                    { print_tag(yytext); }
.                            { /* Ignore everything else */ }

%%

int main(int argc, char *argv[]) {
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

    printf("Total HTML Tags: %d\n", tag_count);

    return 0;
}

int yywrap() {
    return 1;
}
