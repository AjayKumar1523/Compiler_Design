%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%option noyywrap

/* Regular Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT})*
INT_CONST   {DIGIT}+
STR_CONST   \"([^\\\"]|\\.)*\"
CHAR_CONST  \'([^\\\']|\\.)*\'
WS          [ \t\n\r\f\v]+

%%

"/"([^]|\+[^/])\+"/"    { printf("<MULTI-LINE COMMENT>\n"); }
"//"(.*)                      { printf("<SINGLE-LINE COMMENT>\n"); }

"include"                    { printf("<INCLUDE DIRECTIVE>\n"); }
"define"                     { printf("<DEFINE DIRECTIVE>\n"); }
"void"                       { printf("<KEYWORD: void>\n"); }
"int|float|double|char"      { printf("<KEYWORD: %s>\n", yytext); }
"if|else|for|while|do|switch|case|break|continue|return"  { printf("<KEYWORD: %s>\n", yytext); }

{ID}                         { printf("<IDENTIFIER: %s>\n", yytext); }

{INT_CONST}                  { printf("<INTEGER CONSTANT: %s>\n", yytext); }
{STR_CONST}                  { printf("<STRING CONSTANT: %s>\n", yytext); }
{CHAR_CONST}                 { printf("<CHARACTER CONSTANT: %s>\n", yytext); }

"+" | "-" | "*" | "/" | "%" | "++" | "--"  { printf("<OPERATOR: %s>\n", yytext); }
"==" | "!=" | "<" | "<=" | ">" | ">="     { printf("<RELATIONAL OPERATOR: %s>\n", yytext); }
"&&" | "||"                               { printf("<LOGICAL OPERATOR: %s>\n", yytext); }
"!" | "&" | "|" | "^" | "~"               { printf("<BITWISE OPERATOR: %s>\n", yytext); }
"<<=" | ">>=" | "<< " | ">>"              { printf("<SHIFT OPERATOR: %s>\n", yytext); }
"=" | "+=" | "-=" | "*=" | "/=" | "%="    { printf("<ASSIGNMENT OPERATOR: %s>\n", yytext); }

"(" | ")" | "[" | "]" | "{" | "}" | ";" | "," | ":" | "."    { printf("<PUNCTUATION: %s>\n", yytext); }

. { /* Ignore all other characters */ }

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

    return 0;
}
