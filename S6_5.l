%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Structure to store token information
struct Token {
    char type[20];
    char value[100];
};

// Array to store tokens
struct Token tokens[1000];
int token_count = 0;
int input_done = 0;

// Function to add token to array
void add_token(const char* type, const char* value) {
    if (token_count < 1000) {
        strncpy(tokens[token_count].type, type, 19);
        tokens[token_count].type[19] = '\0';
        strncpy(tokens[token_count].value, value, 99);
        tokens[token_count].value[99] = '\0';
        token_count++;
    }
}

%}

%%

"DONE" { input_done = 1; return 0; }  /* Special keyword to end input */

"int"|"char"|"return"|"auto"|"double"|"int"|"struct"|"break"|"else"|"long"|"switch"|"case"|"enum"|"register"|"typedef"|"char"|"extern"|"return"|"union"|"const"|"float"|"short"|"unsigned"|"continue"|"for"|"signed"|"void"|"default"|"goto"|"sizeof"|"volatile"|"do"|"if"|"static"|"while"   { add_token("Keyword", yytext); }

[0-9]+[a-zA-Z_][a-zA-Z0-9_]* { add_token("Error", yytext); printf("Error: Invalid identifier '%s' - cannot start with a number\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { add_token("Identifier", yytext); }
[0-9]+ { add_token("Constant", yytext); }
[=+*/-] { add_token("Operator", yytext); }
['"].['"] { add_token("String", yytext); }
[{}()\[\],;] { add_token("Punctuation", yytext); }
"//".*\n { /* Ignore single-line comments */ }
"/*"([^*]|(\*+[^*/]))*"*/" { /* Ignore multi-line comments */ }
[ \t\n] { /* Ignore whitespace */ }
. { add_token("Unknown", yytext); }

%%

int main()
{
    printf("Enter code (Type 'DONE' on a new line and press Enter to finish):\n");
    yylex();
    
    // Print all collected tokens
    printf("\nAll Tokens:\n");
    printf("--------------------\n");
    for(int i = 0; i < token_count; i++) {
        if (strcmp(tokens[i].type, "Error") != 0) {  // Don't print error tokens
            printf("%s: %s\n", tokens[i].type, tokens[i].value);
        }
    }
    printf("--------------------\n");
    printf("Total valid tokens: %d\n", token_count);
    
    return 0;
}

int yywrap() {
    return 1;
}