%option noyywrap
%{
    #include<stdio.h>
    
%}

%%

[0-9]+    { printf("%s\n",yytext); }   
.               ;          

%%

int main() {
    printf("Enter any string: ");  
    yylex();
    return 0;
}