#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Shell {
private:
    string vfs_name;
    bool running;

    //парсер команд с поддержкой кавычек
    vector<string> parseCommand(const string& input) {
        vector<string> args;
        stringstream ss(input);
        string token;
        bool in_quotes = false;
        char quote_char = '"';
        while (ss >> ws) {
            char c = ss.peek();
            if (c == '"' || c == '\'') {
                in_quotes = !in_quotes;
                quote_char = c;
                ss.get();
                continue;
            }
            if (in_quotes) {
                //чит до закр кавычек
                string quoted_token;
                while (ss.get(c) && c != quote_char) {
                    quoted_token += c;
                }
                args.push_back(quoted_token);
                in_quotes = false;
            }
            else {
                //обычный аргумент
                if (ss >> token) {
                    args.push_back(token);
                }
            }
        }
        return args;
    }

    void executeCommand(const vector<string>& args) {
        if (args.empty()) return;

        string command = args[0];
        if (command == "exit") {
            running = false;
            cout << "Выход из эмулятора..." << endl;
        }
        else if (command == "ls") {
            cout << "Команда 'ls' (заглушка) с аргументами: ";
            for (size_t i = 1; i < args.size(); i++) {
                cout << "[" << args[i] << "] ";
            }
            cout << endl;
        }
        else if (command == "cd") {
            cout << "Команда 'cd' (заглушка) с аргументами: ";
            for (size_t i = 1; i < args.size(); i++) {
                cout << "[" << args[i] << "] ";
            }
            cout << endl;
        }
        else {
            cout << "Ошибка: неизвестная команда '" << command << "'" << endl;
        }
    }

public:
    Shell(const string& name) : vfs_name(name), running(true) {}

    void run() {
        cout << "Эмулятор командной оболочки ОС" << endl;
        cout << "VFS: " << vfs_name << endl;
        cout << "Введите 'exit' для выхода" << endl << endl;
        while (running) {
            //приглашение к вводу
            cout << vfs_name << "> ";
            //чтение ввода
            string input;
            getline(cin, input);
            //парсинг и выполнение команды
            auto args = parseCommand(input);
            if (!args.empty()) {
                executeCommand(args);
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    //эмулятор с именем VFS
    Shell shell("VFS");
    shell.run();
    return 0;
}