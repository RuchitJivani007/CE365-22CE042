#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> firstSet;
map<char, set<char>> followSet;
set<char> nonTerminals;

void calculateFirst(char symbol)
{
    if (firstSet.find(symbol) != firstSet.end()) return;

    for (string production : grammar[symbol])
    {
        if (!isupper(production[0]))
        {
            firstSet[symbol].insert(production[0]);
        }
        else
        {
            int i = 0;
            while (i < production.size())
            {
                char nextSymbol = production[i];
                if (isupper(nextSymbol))
                {
                    calculateFirst(nextSymbol);
                    bool hasEpsilon = false;
                    for (char ch : firstSet[nextSymbol])
                    {
                        if (ch == '@')
                        {
                            hasEpsilon = true;
                        }
                        else
                        {
                            firstSet[symbol].insert(ch);
                        }
                    }
                    if (!hasEpsilon) break;
                }
                else
                {
                    firstSet[symbol].insert(nextSymbol);
                    break;
                }
                i++;
            }
        }
    }
}

void calculateFollow(char symbol)
{
    if (followSet.find(symbol) != followSet.end()) return;

    if (symbol == 'S') followSet[symbol].insert('$');

    for (auto rule : grammar)
    {
        char left = rule.first;
        for (string production : rule.second)
        {
            for (int i = 0; i < production.size(); i++)
            {
                if (production[i] == symbol)
                {
                    if (i + 1 < production.size())
                    {
                        char nextSymbol = production[i + 1];
                        if (isupper(nextSymbol))
                        {
                            for (char ch : firstSet[nextSymbol])
                            {
                                if (ch != '@') followSet[symbol].insert(ch);
                            }
                            if (firstSet[nextSymbol].count('@'))
                            {
                                calculateFollow(left);
                                for (char ch : followSet[left])
                                {
                                    followSet[symbol].insert(ch);
                                }
                            }
                        }
                        else
                        {
                            followSet[symbol].insert(nextSymbol);
                        }
                    }
                    else
                    {
                        if (left != symbol)
                        {
                            calculateFollow(left);
                            for (char ch : followSet[left])
                            {
                                followSet[symbol].insert(ch);
                            }
                        }
                    }
                }
            }
        }
    }
}

void printSet(map<char, set<char>> &s)
{
    for (auto entry : s)
    {
        cout << " " << entry.first << " -> { ";
        for (char ch : entry.second)
        {
            cout << ch << " ";
        }
        cout << "}" << endl;
    }
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

    cout << "\nFirst Sets:\n";
    printSet(firstSet);

    for (char nt : nonTerminals)
    {
        calculateFollow(nt);
    }

    cout << "\nFollow Sets:\n";
    printSet(followSet);

    return 0;
}
