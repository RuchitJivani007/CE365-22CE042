#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

struct Quadruple
{
    string op, arg1, arg2, result;
};

vector<Quadruple> quadruples;
int tempVarCount = 1;

string newTemp()
{
    return "t" + to_string(tempVarCount++);
}

string parseExpression(istringstream &tokens);
string parseTerm(istringstream &tokens);
string parseFactor(istringstream &tokens);

string parseFactor(istringstream &tokens)
{
    string token;
    tokens >> token;
    if (isdigit(token[0]))
    {
        return token;
    }
    else if (token == "(")
    {
        string res = parseExpression(tokens);
        tokens >> token;
        return res;
    }
    return "";
}

string parseTerm(istringstream &tokens)
{
    string left = parseFactor(tokens);
    string token;
    while (tokens >> token && (token == "*" || token == "/"))
    {
        string right = parseFactor(tokens);
        string temp = newTemp();
        quadruples.push_back({token, left, right, temp});
        left = temp;
    }
    if (!tokens.eof()) tokens.putback(token[0]);
    return left;
}

string parseExpression(istringstream &tokens)
{
    string left = parseTerm(tokens);
    string token;
    while (tokens >> token && (token == "+" || token == "-"))
    {
        string right = parseTerm(tokens);
        string temp = newTemp();
        quadruples.push_back({token, left, right, temp});
        left = temp;
    }
    if (!tokens.eof()) tokens.putback(token[0]);
    return left;
}

void generateQuadruples(const string &expr)
{
    quadruples.clear();
    tempVarCount = 1;
    istringstream tokens(expr);
    parseExpression(tokens);
}

void printQuadruples()
{
    cout << "\nOperator\tOperand1\tOperand2\tResult" << endl;
    for (const auto &q : quadruples)
    {
        cout << q.op << "\t\t" << q.arg1 << "\t\t" << q.arg2 << "\t\t" << q.result << endl;
    }
}

int main()
{
    string expr;
    while (true)
    {
        cout << "\nEnter an expression (or 'exit' to quit): ";
        getline(cin, expr);
        if (expr == "exit") break;

        generateQuadruples(expr);
        printQuadruples();
    }

    return 0;
}
