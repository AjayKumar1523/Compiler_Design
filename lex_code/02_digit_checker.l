%{
#include <stdio.h>
%}

%%
[0-9]  { printf("%s is a digit\n", yytext); }
[^0-9] { printf("%s is not a digit\n", yytext); }
%%

int main(void) 
{
    printf("Enter String:\n");
    yylex();
    return 0;
}

int yywrap(void)
{
    return 1;
}
