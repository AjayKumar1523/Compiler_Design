%{
#include <stdio.h>
%}

%%
[aeiouAEIOU][a-zA-Z]* { printf("Accepted: %s\n", yytext); }
.|\n { /* Ignore other strings */ }
%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
