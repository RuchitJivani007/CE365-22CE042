#include <iostream>
#include <string>

class RecursiveDescentParser {
private:
    std::string input;
    size_t index;

    char current_char() {
        return (index < input.length()) ? input[index] : '\0';
    }

    void consume() {
        index++;
    }

    bool parse_S() {
        if (current_char() == '(') {
            consume();
            if (parse_L()) {
                if (current_char() == ')') {
                    consume();
                    return true;
                }
            }
            return false;
        } else if (current_char() == 'a') {
            consume();
            return true;
        }
        return false;
    }

    bool parse_L() {
        if (parse_S()) {
            return parse_L_prime();
        }
        return false;
    }

    bool parse_L_prime() {
        if (current_char() == ',') {
            consume();
            if (parse_S()) {
                return parse_L_prime();
            }
            return false;
        }
        return true;
    }

public:
    RecursiveDescentParser(const std::string& str) : input(str), index(0) {}

    bool validate() {
        bool result = parse_S();
        return result && index == input.length();
    }
};

int main() {
    int test_cases;
    std::cout << "Enter number of test cases: ";
    std::cin >> test_cases;
    std::cin.ignore(); // Ignore the newline character after integer input

    for (int i = 0; i < test_cases; ++i) {
        std::string input_string;
        std::cout << "Enter a string: ";
        std::getline(std::cin, input_string);

        RecursiveDescentParser parser(input_string);
        
        if (parser.validate()) {
            std::cout << "Valid string" << std::endl;
        } else {
            std::cout << "Invalid string" << std::endl;
        }
    }

    return 0;
}
