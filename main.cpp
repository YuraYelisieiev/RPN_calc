#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;


string convert(const string &exp);

void work_stack(const char &input, stack<double> &myStack);

int main() {
    cout << "This calculator enter your expression" << endl;
    stack<double> myStack;
    string input;
    getline(cin, input);
    input = convert(input);
    for (int i = 0; i < input.size(); i++) {
        string number;
        if (isspace(input[i])) continue;
        else if (isdigit(input[i])) {
            double num = input[i] - '0';
            myStack.push(num);
        } else
            work_stack(input[i], myStack);
    }
    while (!myStack.empty()) {
        myStack.pop();
    }
}

bool isOperator(const char &input) {
    char ops[] = {'-', '+', '*', '/', '^'};
    for (char op : ops) {
        if (input == op) {
            return true;
        }
    }
    return false;
}

void work_stack(const char &input, stack<double> &myStack) {
    double left, right, result;
    right = myStack.top();
    myStack.pop();

    left = myStack.top();
    myStack.pop();

    if (input == '-') {
        result = left - right;
    } else if (input == '+') {
        result = left + right;
    } else if (input == '*') {
        result = left * right;
    } else if (input == '^') {
        result = pow(left, right);
    } else {
        result = left / right;
    }
    myStack.push(result);
    cout << result << endl;
}

int priority(const char &x) {
    if (x == '(') {
        return 0;
    } else if (x == '+' || x == '-') {
        return 1;
    } else if (x == '*' || x == '/') {
        return 2;
    } else if (x == '^') {
        return 3;
    } else {
        return -1;
    }
}

bool IsOperand(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

string convert(const string &exp) {
    stack<char> myStack;
    string postfix;
    for (auto &elem: exp) {
        if (elem == ' ' || elem == ',') continue;

        else if (isOperator(elem)) {
            while (!myStack.empty() && myStack.top() != '(' && priority(myStack.top()) >= priority(elem)) {
                postfix += myStack.top();
                myStack.pop();
            }
            myStack.push(elem);
        } else if (IsOperand(elem)) {
            postfix += elem;
        } else if (elem == '(') {
            myStack.push(elem);
        } else if (elem == ')') {
            while (!myStack.empty() && myStack.top() != '(') {
                postfix += myStack.top();
                myStack.pop();
            }
            myStack.pop();
        }
    }
    while (!myStack.empty()) {
        postfix += myStack.top();
        myStack.pop();
    }
    return postfix;
}