%{
    #include<stdio.h>
    int digit = 0,lower = 0,upper = 0,special = 0,length = 0,count = 0;
%}

%%

[0-9]   {digit++; length++;}
[a-z]   {lower++; length++;}
[A-Z]   {upper++; length++;}
[*, ; # $ @]    {special++; length++;}
[\n]    {
            if(count>0)
                printf("invalid password\n");

            else if(length>9&&length<15&&lower>0&&upper>0&&special>0&&digit>0&&count<1)
                printf("valid password\n");
            else
                printf("invalid password\n");
                length=lower=upper=special=digit=count=0;
            }
.   {count++;}

%%

int main() {
    printf("Enter password: ");  
    yylex();
    return 0;
}

int yywrap(){
}