#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

// List of valid C data types
const char *validTypes[] = {"int", "float", "char", "double"};
const int typeCount = 4;

// List of C reserved keywords (subset)
const char *reservedKeywords[] = {"if", "else", "while", "return", "for", "switch", "case", "break", "continue", "typedef", "struct", "union"};
const int keywordCount = 12;

// Function to check if a string is a valid data type
bool isValidType(char *type) {
    for (int i = 0; i < typeCount; i++) {
        if (strcmp(type, validTypes[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if a string is a reserved keyword
bool isReservedKeyword(char *word) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(word, reservedKeywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if a variable name is valid
bool isValidIdentifier(char *name) {
    if (!isalpha(name[0]) && name[0] != '_') return false; // Must start with letter or underscore
    for (int i = 1; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != '_') return false;
    }
    return !isReservedKeyword(name);
}

// Function to check if a string is a valid numeric value
bool isValidNumber(char *value) {
    char *endptr;
    strtod(value, &endptr);
    return *endptr == '\0';
}

// Function to analyze a variable declaration
void analyzeDeclaration(char *declaration) {
    char type[20], name[50], assign[5], value[50];
    int len = strlen(declaration);
    
    // Check if the last character is a semicolon
    if (len == 0 || declaration[len - 1] != ';') {
        printf("Syntax Error: Missing semicolon at the end.\n");
        return;
    }
    
    // Remove semicolon for processing
    declaration[len - 1] = '\0'; 
    
  
    int parts = sscanf(declaration, "%19s %49s %4s %49s", type, name, assign, value);
    
    if (parts < 2 || parts > 4) {
        printf("Syntax Error: Invalid declaration format.\n");
        return;
    }
    
    if (!isValidType(type)) {
        printf("Error: Invalid data type '%s'\n", type);
        return;
    }
    
    if (!isValidIdentifier(name)) {
        printf("Error: Invalid identifier '%s'\n", name);
        return;
    }
    
    if (parts == 4) { // Checking initialization
        if (strcmp(assign, "=") != 0) {
            printf("Syntax Error: Expected '=' for initialization but found '%s'.\n", assign);
            return;
        }
        if (!isValidNumber(value)) {
            printf("Syntax Error: Invalid initialization value '%s'.\n", value);
            return;
        }
    }
    
    printf("Valid variable declaration: %s;\n", declaration);
}

int main() {
    char input[100];
    while (1) {
        printf("Enter C variable declaration (or 'exit' to quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline
        
        if (strcmp(input, "exit") == 0) {
            break;
        }
        
        analyzeDeclaration(input);
    }
    return 0;
}