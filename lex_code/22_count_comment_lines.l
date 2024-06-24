%{
#include <stdio.h>
int comment_line_count = 0;
%}

%option noyywrap

%%

"/*"    {
            comment_line_count++;
            int in_comment = 1;
            while (in_comment) {
                char c = input();
                if (c == EOF) {
                    return 0;
                } else if (c == '*') {
                    c = input();
                    if (c == '/') {
                        in_comment = 0;
                    } else {
                        unput(c);
                    }
                } else if (c == '\n') {
                    comment_line_count++;
                }
            }
        }

"//"    {
            comment_line_count++;
            while (1) {
                char c = input();
                if (c == EOF || c == '\n') {
                    return 0;
                }
            }
        }

.       {
            // Ignore other characters
        }

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

    printf("Total Comment Lines: %d\n", comment_line_count);

    return 0;
}

