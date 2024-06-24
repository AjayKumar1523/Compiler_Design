%{
#include <stdio.h>

int char_count = 0;
int line_count = 0;
int word_count = 0;

void count_words(char *text) {
    char *p = text;
    int in_word = 0;
    while (*p) {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || (*p >= '0' && *p <= '9') || *p == '_') {
            if (!in_word) {
                in_word = 1;
                word_count++;
            }
        } else {
            in_word = 0;
        }
        p++;
    }
}

%}

%%

[a-zA-Z]+ {
    count_words(yytext);
}

[ \t]+ {
    // Ignore spaces and tabs
}

\n {
    line_count++;
}

. {
    char_count++;
}

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

    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count + 1);

    return 0;
}

int yywrap() {
    return 1;
}
