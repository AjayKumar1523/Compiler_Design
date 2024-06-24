%{
#include <stdio.h>
#include <string.h>

int max_length = 0;
%}

%%
[a-zA-Z]+ {
    int length = yyleng;
    if (length > max_length) {
        max_length = length;
    }
}
.|\n { /* Ignore other characters and newlines */ }
%%

int main(int argc, char **argv) {
    yylex();
    printf("Length of the longest word: %d\n", max_length);
    return 0;
}

int yywrap() {
    return 1;
}
