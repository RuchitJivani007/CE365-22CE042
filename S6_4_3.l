%option noyywrap

%{
#include <stdio.h>
int Char = 0,word = 0,line = 0;
%}

%%

\n      { line++; Char++; } 
[ \t]+  { Char += yyleng; }     
[a-zA-Z0-9]+ { word++; Char +=yyleng; } 
.       { Char++; }              
%%

int main() {
    printf("Enter a line : ");
    yylex(); 
    printf("Characters : %d\n", Char);
    printf("Words      : %d\n", word);
    printf("Lines      : %d\n", line);

    return 0;
}


