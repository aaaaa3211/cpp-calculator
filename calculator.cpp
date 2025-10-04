#include "calculator.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

map<string, double> vars;

double factorial(double n) {
    if (n < 0) throw runtime_error("Помилка: факторіал від'ємного числа!");
    double f = 1;
    for (int i = 1; i <= int(n); i++) f *= i;
    return f;
}

double compute(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw runtime_error("Помилка: ділити на 0 не можна!");
        return a / b;
    case '^': return pow(a, b);
    }
    return 0;
}

double eval_simple(string expr) {
    string s;
    for (char c : expr) if (c != ' ') s += c;
    expr = s;

    if (expr.find("sqrt(") == 0) {
        size_t start = expr.find('(') + 1;
        size_t end = expr.find(')');
        string arg = expr.substr(start, end - start);
        double val = eval(arg);
        if (val < 0) throw runtime_error("Помилка: квадратний корінь з від'ємного числа!");
        return sqrt(val);
    }

    size_t fpos = expr.find('!');
    if (fpos != string::npos) {
        double val = eval(expr.substr(0, fpos));
        return factorial(val);
    }

    if (expr.size() >= 2 && expr.substr(expr.size() - 2) == "^2") {
        double val = eval(expr.substr(0, expr.size() - 2));
        return pow(val, 2);
    }

    if (expr.size() >= 2 && expr.substr(expr.size() - 2) == "^3") {
        double val = eval(expr.substr(0, expr.size() - 2));
        return pow(val, 3);
    }

    if (expr[0] == '(' && expr[expr.size() - 1] == ')')
        return eval(expr.substr(1, expr.size() - 2));

    int par = 0;
    for (int i = expr.size() - 1; i >= 0; i--) {
        char c = expr[i];
        if (c == ')') par++;
        if (c == '(') par--;
        if (par == 0 && (c == '+' || c == '-'))
            return compute(eval(expr.substr(0, i)), eval(expr.substr(i + 1)), c);
    }

    par = 0;
    for (int i = expr.size() - 1; i >= 0; i--) {
        char c = expr[i];
        if (c == ')') par++;
        if (c == '(') par--;
        if (par == 0 && (c == '*' || c == '/'))
            return compute(eval(expr.substr(0, i)), eval(expr.substr(i + 1)), c);
    }

    par = 0;
    for (int i = expr.size() - 1; i >= 0; i--) {
        char c = expr[i];
        if (c == ')') par++;
        if (c == '(') par--;
        if (par == 0 && c == '^')
            return compute(eval(expr.substr(0, i)), eval(expr.substr(i + 1)), c);
    }

    if (vars.find(expr) != vars.end()) return vars[expr];
    return stod(expr);
}

double eval(string expr) {
    size_t pos = expr.find('=');
    if (pos != string::npos) {
        string var = expr.substr(0, pos);
        string val = expr.substr(pos + 1);
        double result = eval(val);
        vars[var] = result;
        return result;
    }
    else return eval_simple(expr);
}
