// • String over 0 and 1 where every 0 immediately followed by 11 (take a for 0 & b for 1 in input symbols)
// • string over a b c, starts and end with same letter.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int inputSymbolsNo;
    int statesNo;
    int initialState;
    int acceptingStatesNo;

    cout << "Enter the number of input symbols: ";
    cin >> inputSymbolsNo;

    cout << "Enter the input symbols: ";
    char inputSymbols[inputSymbolsNo];
    for (int i = 0; i < inputSymbolsNo; i++) {
        cin >> inputSymbols[i];
    }

    cout << "Enter the number of states: ";
    cin >> statesNo;
    cout << "Enter the initial state: ";
    cin >> initialState;

    cout << "Enter the number of accepting states: ";
    cin >> acceptingStatesNo;

    int acceptingStates[acceptingStatesNo];
    cout << "Enter the accepting states: ";
    for (int i = 0; i < acceptingStatesNo; i++) {
        cin >> acceptingStates[i];
    }

    int transitionTable[statesNo + 1][inputSymbolsNo]; 
    for (int i = 1; i <= statesNo; i++) {  
        for (int j = 0; j < inputSymbolsNo; j++) {
            cout << "Enter the transition for state " << i << " and input symbol " << inputSymbols[j] << ": ";
            cin >> transitionTable[i][j];
        }
    }

    string inputString;
    int choice;
    do {
        cout << "Enter the input string: ";
        cin >> inputString;

        int currentState = initialState;
        int flag = 0;

        for (char c : inputString) {
            int symbolIndex = -1;
            for (int i = 0; i < inputSymbolsNo; i++) {
                if (c == inputSymbols[i]) {
                    symbolIndex = i;
                    break;
                }
            }

            if (symbolIndex == -1) {
                flag = 0;
                break;  
            }

            currentState = transitionTable[currentState][symbolIndex];
        }

        for (int i = 0; i < acceptingStatesNo; i++) {
            if (currentState == acceptingStates[i]) {
                flag = 1;
                break;
            }
        }

        if (flag) {
            cout << "Valid string" << endl;
        } else {
            cout << "Invalid string" << endl;
        }

        cout << "Enter 1 for other string validation and 0 for exit: ";
        cin >> choice;
    } while (choice != 0);

    return 0;
}
