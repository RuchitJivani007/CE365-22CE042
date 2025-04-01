#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "first_follow.h"

using namespace std;

extern map<char, vector<string>> grammar;
extern map<char, set<char>> firstSet;
extern map<char, set<char>> followSet;
extern set<char> nonTerminals;

map<pair<char, char>, string> parsingTable;

void createParsingTable()
{
    for (auto rule : grammar)
    {
        char left = rule.first;
        for (string production : rule.second)
        {
            if (!isupper(production[0]))
            {
                if (production[0] != '@')
                {
                    parsingTable[ {left, production[0]}] = production;
                }
                else
                {
                    for (char ch : followSet[left])
                    {
                        parsingTable[ {left, ch}] = production;
                    }
                }
            }
            else
            {
                for (char ch : firstSet[production[0]])
                {
                    if (ch != '@')
                    {
                        parsingTable[ {left, ch}] = production;
                    }
                }
                if (firstSet[production[0]].count('@'))
                {
                    for (char ch : followSet[left])
                    {
                        parsingTable[ {left, ch}] = production;
                    }
                }
            }
        }
    }
}

bool isLL1Grammar()
{
    for (auto rule : grammar)
    {
        set<char> seen;
        for (string production : rule.second)
        {
            set<char> first;
            if (!isupper(production[0]))
            {
                first.insert(production[0]);
            }
            else
            {
                first = firstSet[production[0]];
            }
            for (char ch : first)
            {
                if (seen.count(ch))
                {
                    return false;
                }
                seen.insert(ch);
            }
        }
    }
    return true;
}

bool validateString(string input)
{
    input += '$';
    string stack = "S$";
    int i = 0;
    while (!stack.empty())
    {
        char top = stack.back();
        stack.pop_back();
        if (top == input[i])
        {
            i++;
        }
        else if (isupper(top))
        {
            if (parsingTable.count({top, input[i]}))
            {
                string production = parsingTable[ {top, input[i]}];
                if (production != "@")
                {
                    for (int j = production.size() - 1; j >= 0; j--)
                    {
                        stack.push_back(production[j]);
                    }
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    return i == input.size();
}

int main()
{
    int n;
    cout << "Enter number of rules: ";
    cin >> n;
    cout << "Enter grammar rules in the form A -> BCD (use @ for epsilon):\n";
    for (int i = 0; i < n; i++)
    {
        char left;
        string arrow, right;
        cin >> left >> arrow >> right;
        grammar[left].push_back(right);
        nonTerminals.insert(left);
    }

    for (char nt : nonTerminals)
    {
        calculateFirst(nt);
    }
    for (char nt : nonTerminals)
    {
        calculateFollow(nt);
    }

    cout << "\nFirst Sets:\n";
    printSet(firstSet);

    cout << "\nFollow Sets:\n";
    printSet(followSet);

    createParsingTable();

    cout << "\nPredictive Parsing Table:\n";
    for (auto entry : parsingTable)
    {
        cout << "M[" << entry.first.first << ", " << entry.first.second << "] = " << entry.second << endl;
    }

    if (isLL1Grammar())
    {
        cout << "\nGrammar is LL(1)\n";
    }
    else
    {
        cout << "\nGrammar is NOT LL(1)\n";
        return 0;
    }

    string input;
    cout << "\nEnter input string: ";
    cin >> input;

    if (validateString(input))
    {
        cout << "\nValid string\n";
    }
    else
    {
        cout << "\nInvalid string\n";
    }

    return 0;
}
