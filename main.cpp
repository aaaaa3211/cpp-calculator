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
        cout << "\n=== ������� ����������� ===\n";
        cout << "1. ���������� (+ - * /)\n";
        cout << "2. ϳ�������� �� ������� (^, ^2, ^3)\n";
        cout << "3. �������� (!)\n";
        cout << "4. ���������� ����� (sqrt)\n";
        cout << "5. ������������ ������\n";
        cout << "6. �������� ������ (history.txt)\n";
        cout << "0. �����\n";
        cout << "������ �������: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == int(MenuOption::Exit)) break;

        string input;
        double result;

        try {
            switch (MenuOption(choice)) {
            case MenuOption::Arithmetic:
                cout << "������ ����� (+ - * /): ";
                getline(cin, input);
                result = eval(input);
                cout << "���������: " << result << endl;
                save_history(input + " = " + to_string(result));
                break;
            case MenuOption::Power:
                cout << "������ ����� ��� ������� (^, ^2, ^3): ";
                getline(cin, input);
                result = eval(input);
                cout << "���������: " << result << endl;
                save_history(input + " = " + to_string(result));
                break;
            case MenuOption::Factorial:
                cout << "������ ����� ��� ���������: ";
                getline(cin, input);
                result = eval(input + "!");
                cout << "���������: " << result << endl;
                save_history(input + "! = " + to_string(result));
                break;
            case MenuOption::Sqrt:
                cout << "������ ����� ��� sqrt: ";
                getline(cin, input);
                result = eval("sqrt(" + input + ")");
                cout << "���������: " << result << endl;
                save_history("sqrt(" + input + ") = " + to_string(result));
                break;
            case MenuOption::Variables:
                cout << "������ ����� � ������� (x=5 ��� x+2): ";
                getline(cin, input);
                result = eval(input);
                cout << "���������: " << result << endl;
                save_history(input + " = " + to_string(result));
                break;
            case MenuOption::History:
                show_history();
                break;
            default:
                cout << "������� ����!\n";
            }
        }
        catch (runtime_error& e) {
            cout << e.what() << endl;
        }
        catch (...) {
            cout << "������� � �����!\n";
        }
    }

    cout << "����� �� ������������ �������������!\n";
    return 0;
}
