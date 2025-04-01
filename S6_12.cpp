#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

bool isNumber(const string &s)
{
    for (char c : s)
    {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

string evaluateExpression(const string &expr)
{
    istringstream iss(expr);
    vector<string> tokens;
    string token;

    while (iss >> token) tokens.push_back(token);

    for (int i = 0; i < tokens.size(); i++)
    {
        if (i + 2 < tokens.size() && isNumber(tokens[i]) && isNumber(tokens[i + 2]))
        {
            double left = stod(tokens[i]);
            double right = stod(tokens[i + 2]);
            string op = tokens[i + 1];
            double result = 0;

            if (op == "+") result = left + right;
            else if (op == "-") result = left - right;
            else if (op == "*") result = left * right;
            else if (op == "/") result = left / right;

            tokens[i] = to_string(result);
            tokens.erase(tokens.begin() + i + 1, tokens.begin() + i + 3);
            i--;
        }
    }

    string result;
    for (string &t : tokens) result += t + " ";
    return result;
}

int main()
{
    string expr;
    while (true)
    {
        cout<<"\nEnter expression (enter exit for break): ";
        getline(cin, expr);
        if (expr == "exit") break;
        cout <<"output: "<< evaluateExpression(expr) << endl;
    }
}
