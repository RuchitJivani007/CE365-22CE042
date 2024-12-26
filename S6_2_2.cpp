#include <bits/stdc++.h>
using namespace std;

int main()
{
    int numofsymbol = 36, numofstates = 3, initialstate = 1, numofas = 1;
    char charArray[36];
    int index = 0;

    // Populate charArray with 'a' to 'z' and '0' to '9'
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        charArray[index++] = ch;
    }
    for (char ch = '0'; ch <= '9'; ch++)
    {
        charArray[index++] = ch;
    }

    // Hardcoded transition table
    int transitiontable[3][36];
    for (int i = 0; i < 36; i++)
    {
        if (i < 26)
        {
            // From initial state (1), lowercase alphabets lead to state 2
            transitiontable[1][i] = 2;
        }
        else
        {
            // From initial state (1), digits lead to dead state (0)
            transitiontable[1][i] = 0;
        }
        // From state 2, both alphabets and digits stay in state 2
        transitiontable[2][i] = 2;
    }

    // Input for accepting states
    int acceptingSTATE = 2;

    cout << "Input string: ";
    string Inputstring;
    cin >> Inputstring;

    // Validation logic
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

    // Check if the final state is accepting
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