%{
#include <stdio.h>
%}

%%
[a-zA-Z]+ { printf("Word: %s\n", yytext); }
"=="|"<="|">="|"<"|">"|"!=" { printf("Relational operator: %s\n", yytext); }
[ \t\n]   { /* Ignore whitespace */ }
.         { /* Ignore other characters */ }
%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
