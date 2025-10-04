# Вариант №1
Условия задания
Разработать эмулятор для языка оболочки ОС. Необходимо сделать работу эмулятора как можно более похожей на работу в командной строке UNIX подобной ОС.

## Содержание:
- [Этап 1. REPL](#этап-1-repl)
- [Результат 1 этапа](#результат-1-этапа)
- [Этап 2. Конфигурация](#этап-2-конфигурация)
- [Результат 2 этапа](#результат-2-этапа)

## Этап 1. REPL

**Цель**: создать минимальный прототип. Большинство функций в нем пока
представляют собой заглушки, но диалог с пользователем уже поддерживается.

### Требования:
1. Приложение должно быть реализовано в форме консольного интерфейса
(CLI).
2. Приглашение к вводу должно содержать имя VFS.
3. Реализовать парсер, который корректно обрабатывает аргументы в кавычках.
4. Сообщить об ошибке выполнения команд (неизвестная команда, неверные
аргументы).
5. Реализовать команды-заглушки, которые выводят свое имя и аргументы: ls,
cd.
6. Реализовать команду exit.
7. Продемонстрировать работу прототипа в интерактивном режиме.
Необходимо показать примеры работы всей реализованной функциональности, включая обработку ошибок.
8. Результат выполнения этапа сохранить в репозиторий стандартно оформленным коммитом.

### Результат 1 этапа
<img width="563" height="280" alt="image" src="https://github.com/user-attachments/assets/95d9cb8f-fdec-468a-8cd5-9885e89bb2cb" />

### Код 1 этапа реализованного на языке С++
```
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
```

## Этап 2. Конфигурация
**Цель**: сделать эмулятор настраиваемым, то есть поддержать ввод параметров пользователя в приложение. Организовать для этого этапа отладочный вывод всех заданных параметров при запуске эмулятора.
### Требования:
1. Параметры командной строки:
– Путь к физическому расположению VFS.
– Путь к стартовому скрипту.
2. Стартовый скрипт для выполнения команд эмулятора: останавливается при первой ошибке. При выполнении скрипта на экране отображается как ввод, так и вывод, имитируя диалог с пользователем.
3. Сообщить об ошибке во время исполнения стартового скрипта.
4. Реализовать вывод параметров эмулятора в формате ключ-значение с помощью служебной команды conf-dump.
5. Создать несколько скриптов реальной ОС, в которой выполняется эмулятор. Включить в каждый скрипт вызовы эмулятора для тестирования всех поддерживаемых параметров командной строки.
6. Результат выполнения этапа сохранить в репозиторий стандартно оформленным коммитом.

### Результат 2 этапа
<img width="1116" height="465" alt="image" src="https://github.com/user-attachments/assets/5b88a4e1-acd6-4839-9d6e-0dd7918423ca" />


Проверено: 
Параметры командной строки корректно обрабатываются.
Скрипт выполняется построчно с имитацией диалога.
При неизвестной команде скрипт останавливается.
Команда conf-dump выводит актуальную конфигурацию.
Отладочный вывод параметров работает при запуске.

Тестовые скрипты:
test_script.txt - демонстрация работы команд.
------------------------------
ls

cd /home/user

conf-dump

echo "Test zavershen"

error_script.txt - проверка остановки при ошибке
------------------------------
ls

invalid_command

cd /home

### Код 2 этапа реализованного на языке С++
```
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

class Shell {
private:
    string vfs_name;
    bool running;
    string vfs_path;    // новый параметр
    string script_path; // новый параметр

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

    //НОВ.ФУН: вывод конфигурации
    void showConfig() {
        cout << "Конфигурация эмулятора" << endl;
        cout << "vfs_path: " << (vfs_path.empty() ? "не указан" : vfs_path) << endl;
        cout << "script_path: " << (script_path.empty() ? "не указан" : script_path) << endl;
    }

    //НОВ.ФУН: выполнение скрипта
    bool executeScript(const string& script_path) {
        ifstream file(script_path);
        if (!file.is_open()) {
            cout << "Ошибка: не удалось открыть скрипт '" << script_path << "'" << endl;
            return false;
        }

        cout << " Выполнение скрипта: " << script_path << " ===" << endl;

        string line;
        int line_num = 0;

        while (getline(file, line)) {
            line_num++;

            //пропускаем пустые строки и комментарии
            if (line.empty() || line[0] == '#') {
                continue;
            }

            //показываем ввод (имитация диалога)
            cout << "VFS> " << line << endl;

            //выполняем команду
            auto args = parseCommand(line);
            if (!args.empty()) {
                string command = args[0];

                if (command == "exit") {
                    cout << "Скрипт прерван командой exit на строке " << line_num << endl;
                    return false;
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
                else if (command == "conf-dump") {
                    showConfig();
                }
                else {
                    cout << "Ошибка: неизвестная команда '" << command << "' на строке " << line_num << endl;
                    cout << "Скрипт остановлен из-за ошибки" << endl;
                    return false;
                }
            }
        }

        cout << "Скрипт успешно выполнен" << endl;
        return true;
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
        //НОВ.КОМ: вывод конфигурации
        else if (command == "conf-dump") {
            showConfig();
        }
        else {
            cout << "Ошибка: неизвестная команда '" << command << "'" << endl;
        }
    }

public:
    //ИЗМЕНЕН КОНСТРУКТОР: теперь принимает пути к VFS и скрипту
    Shell(const string& name, const string& vfs_path = "", const string& script_path = "")
        : vfs_name(name), running(true), vfs_path(vfs_path), script_path(script_path) {
    }

    void run() {
        //НОВ.К: отладочный вывод параметров при запуске
        cout << "Отладочный вывод параметров" << endl;
        cout << "vfs_path: " << (vfs_path.empty() ? "не указан" : vfs_path) << endl;
        cout << "script_path: " << (script_path.empty() ? "не указан" : script_path) << endl;

        //НОВ.КОД: выполнение стартового скрипта если указан
        if (!script_path.empty()) {
            if (!executeScript(script_path)) {
                return; //завершаем если скрипт завершился с ошибкой
            }
            cout << endl;
        }
        cout << "Эмулятор командной оболочки ОС" << endl;
        cout << "VFS: " << vfs_name << endl;
        cout << "Введите 'exit' для выхода, 'conf-dump' для просмотра конфигурации" << endl << endl;

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

//НОВ.ФУН: парсер аргументов командной строки
void parseCommandLine(int argc, char* argv[], string& vfs_path, string& script_path) {
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--vfs" && i + 1 < argc) {
            vfs_path = argv[++i];
        }
        else if (arg == "--script" && i + 1 < argc) {
            script_path = argv[++i];
        }
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    //НОВ.К: парсим аргументы командной строки
    string vfs_path, script_path;
    parseCommandLine(argc, argv, vfs_path, script_path);

    //ИЗМЕНЕН.ВЫЗОВ: передаем пути в конструктор
    Shell shell("VFS", vfs_path, script_path);
    shell.run();

    return 0;
}
```

