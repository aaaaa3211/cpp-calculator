#pragma once
#include <string>
#include <map>

using namespace std;

extern map<string, double> vars;

enum class MenuOption {
    Exit = 0,
    Arithmetic = 1,
    Power = 2,
    Factorial = 3,
    Sqrt = 4,
    Variables = 5,
    History = 6
};


double factorial(double n);
double compute(double a, double b, char op);
double eval(string expr);
double eval_simple(string expr);

