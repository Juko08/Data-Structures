#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool matches(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool balanced(const string& expression) {
    stack<char> delimiters;

    for (char ch : expression) {
        if (ch == '(' || ch == '[' || ch == '{') {
            delimiters.push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (delimiters.empty()) {
                return false;
            }

            char opening = delimiters.top();

            if (!matches(opening, ch)) {
                return false;
            }

            delimiters.pop();
        }
    }

    return delimiters.empty();
}

int main() {
    string expressions[] = {
        "{(a+b)*[c-d]}",
        "{(a+b]*c}",
        "((a+b))",
        "((a+b)",
        "[a+b]",
        "{[()]}" ,
        "{[(])}"
    };

    for (const string& expression : expressions) {
        cout << "Expression: " << expression << endl;
        cout << "Balanced: " << boolalpha << balanced(expression) << endl;
        cout << endl;
    }

    return 0;
}
