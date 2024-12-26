#include<stdio.h>
#include<conio.h>
int main()
{
    char string[100];
    int i=0;

    printf("Enter String: ");
    scanf("%s",&string);

    while(string[i]=='a')
    {
        i++;
    }

    if(string[i]=='b' && string[i+1]=='b' && string[i+2]=='\0')
    {
        printf("Valid String.");
    }

    else
    {
        printf("Invalid String.");
    }
}