// • String over lower-case alphabet and digits, starts with alphabet only.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int inputSymbolsNo = 36;
    int statesNo = 3;
    int initialState = 0; 
    int acceptingStatesNo = 1;

    char inputSymbols[36] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int acceptingStates[1] = {1};

    int transitionTable[statesNo][inputSymbolsNo];
    for (int i = 0; i < statesNo; i++) {
        for (int j = 0; j < inputSymbolsNo; j++) {
            if (i == 0 && j < 26) {
                transitionTable[i][j] = 1; 
            } else if (i == 0 && j >= 26) {
                transitionTable[i][j] = 2; 
            } else if (i == 1) {
                transitionTable[i][j] = 1; 
            } else if (i == 2) {
                transitionTable[i][j] = 2; 
            }
        }
    }

    string inputString;
    int choice;
    do {
        cout << "Enter the input string: ";
        cin >> inputString;

        int currentState = initialState;
        bool isValid = true;

        for (char c : inputString) {
            int symbolIndex = -1;
            for (int i = 0; i < inputSymbolsNo; i++) {
                if (c == inputSymbols[i]) {
                    symbolIndex = i;
                    break;
                }
            }

            if (symbolIndex == -1) { 
                isValid = false;
                break;
            }

            currentState = transitionTable[currentState][symbolIndex];
        }

        if (isValid) {
            bool isAccepting = false;
            for (int i = 0; i < acceptingStatesNo; i++) {
                if (currentState == acceptingStates[i]) {
                    isAccepting = true;
                    break;
                }
            }
            if (isAccepting) {
                cout << "Valid string\n";
            } else {
                cout << "Invalid string\n";
            }
        } else {
            cout << "Invalid string: contains unsupported symbols\n";
        }

        cout << "Enter 1 for other string validation and 0 for exit: ";
        cin >> choice;
    } while (choice != 0);

    return 0;
}
