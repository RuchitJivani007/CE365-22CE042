#include <bits/stdc++.h>
using namespace std;

int main()
{
    int numofsymbol = 36, numofstates = 3, initialstate = 1, numofas = 1;
    char charArray[36];
    int index = 0;

    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        charArray[index++] = ch;
    }
    for (char ch = '0'; ch <= '9'; ch++)
    {
        charArray[index++] = ch;
    }

    int transitiontable[3][36];
    for (int i = 0; i < 36; i++)
    {
        if (i < 26)
        {
            transitiontable[1][i] = 2;
        }
        else
        {
            transitiontable[1][i] = 0;
        }
        transitiontable[2][i] = 2;
    }

    int acceptingSTATE = 2;

    cout << "Input string: ";
    string Inputstring;
    cin >> Inputstring;

    int currentstate = initialstate;
    bool isValid = true;

    for (char c : Inputstring)
    {
        bool symbolFound = false;
        for (int j = 0; j < numofsymbol; j++)
        {
            if (c == charArray[j])
            {
                currentstate = transitiontable[currentstate][j];
                symbolFound = true;
                break;
            }
        }
        if (!symbolFound || currentstate == 0)
        {
            isValid = false;
            break;
        }
    }

    if (isValid && currentstate == acceptingSTATE)
    {
        cout << "Valid string" << endl;
    }
    else
    {
        cout << "Invalid string" << endl;
    }

    return 0;
}
