#include <iostream>
#include "calculator.h"
#include "history.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    while (true) {
        cout << "\n=== Базовий калькулятор ===\n";
        cout << "1. Арифметика (+ - * /)\n";
        cout << "2. Піднесення до степеня (^, ^2, ^3)\n";
        cout << "3. Факторіал (!)\n";
        cout << "4. Квадратний корінь (sqrt)\n";
        cout << "5. Використання змінних\n";
        cout << "6. Показати історію (history.txt)\n";
        cout << "0. Вихід\n";
        cout << "Оберіть функцію: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == int(MenuOption::Exit)) break;

        string input;
        double result;

        try {
            switch (MenuOption(choice)) {
            case MenuOption::Arithmetic:
                cout << "Введіть вираз (+ - * /): ";
                getline(cin, input);
                result = eval(input);
                cout << "Результат: " << result << endl;
                save_history(input + " = " + to_string(result));
                break;
            case MenuOption::Power:
                cout << "Введіть вираз для степеня (^, ^2, ^3): ";
                getline(cin, input);
                result = eval(input);
                cout << "Результат: " << result << endl;
                save_history(input + " = " + to_string(result));
                break;
            case MenuOption::Factorial:
                cout << "Введіть число для факторіалу: ";
                getline(cin, input);
                result = eval(input + "!");
                cout << "Результат: " << result << endl;
                save_history(input + "! = " + to_string(result));
                break;
            case MenuOption::Sqrt:
                cout << "Введіть число для sqrt: ";
                getline(cin, input);
                result = eval("sqrt(" + input + ")");
                cout << "Результат: " << result << endl;
                save_history("sqrt(" + input + ") = " + to_string(result));
                break;
            case MenuOption::Variables:
                cout << "Введіть вираз зі змінними (x=5 або x+2): ";
                getline(cin, input);
                result = eval(input);
                cout << "Результат: " << result << endl;
                save_history(input + " = " + to_string(result));
                break;
            case MenuOption::History:
                show_history();
                break;
            default:
                cout << "Невірний вибір!\n";
            }
        }
        catch (runtime_error& e) {
            cout << e.what() << endl;
        }
        catch (...) {
            cout << "Помилка в виразі!\n";
        }
    }

    cout << "Дякую за користування калькулятором!\n";
    return 0;
}
