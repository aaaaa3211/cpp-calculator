#include "history.h"
#include <fstream>
#include <iostream>
using namespace std;

void save_history(const string& entry) {
    ofstream file("history.txt", ios::app);
    if (file.is_open()) {
        file << entry << endl;
        file.close();
    }
}

void show_history() {
    ifstream file("history.txt");
    string line;
    cout << "--- Історія обчислень ---\n";
    while (getline(file, line)) cout << line << endl;
}
