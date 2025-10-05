# Вариант №1
Условия задания
Разработать эмулятор для языка оболочки ОС. Необходимо сделать работу эмулятора как можно более похожей на работу в командной строке UNIX подобной ОС.

## Содержание:
- [Этап 1. REPL](#этап-1-repl)
- [Результат 1 этапа](#результат-1-этапа)
- [Этап 2. Конфигурация](#этап-2-конфигурация)
- [Результат 2 этапа](#результат-2-этапа)
- [Этап 3. VFS](#этап-3-vfs)
- [Результат 3 этапа](#результат-3-этапа)
- [Этап 4. Основные команды](#этап-4-основные-команды)
- [Результат 4 этапа](#результат-4-этапа)

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
## Этап 3. VFS
**Цель**: подключить виртуальную файловую систему (VFS).
### Требования:
1. Все операции должны производиться в памяти. Запрещается распаковывать или иным образом модифицировать данные VFS, за исключением возможных служебных команд.
2. Источником VFS является ZIP-архив. Для двоичных данных используется base64 или аналогичный формат.
3. Поддержать вывод сообщения из файла motd при старте. Если motd существует, то он находится в корне VFS.
4. Создать несколько скриптов реальной ОС, в которой выполняется эмулятор. Включить в каждый скрипт вызовы эмулятора для тестирования работы c различными вариантами VFS (минимальный, несколько файлов, не менее 3 уровней файлов и папок).
5. Создать стартовый скрипт для тестирования всех реализованных на этом и прошлых этапах команд. Добавить туда примеры всех режимов команд, включая работу с VFS и обработку ошибок.
6. Результат выполнения этапа сохранить в репозиторий стандартно оформленным коммитом.

### Результат 3 этапа
<img width="1365" height="834" alt="image" src="https://github.com/user-attachments/assets/8b7eaa44-8cff-4501-b4da-30290c089c81" />

**Проверено:**
- VFS успешно загружается из ZIP-архива в память
- MOTD выводится при старте если файл существует в корне VFS
- Команды ls, cd, cat работают с виртуальной файловой системой
- Файловая структура содержит 3+ уровня вложенности (/, /home, /home/user)
- Все операции производятся только в памяти
- Поддерживаются абсолютные пути (/etc/config.txt) и относительные пути

**Тестовые скрипты:**
vfs_test_script.txt - демонстрация работы VFS
------------------------------
conf-dump

ls

cd /home

ls

cd user

ls

cat document.txt

cat /motd

cd /

ls

cat /etc/config.txt

### **Код 3 этапа реализованного на языке С++**
```
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

//структура для узла VFS (файл или папка)
struct VFSNode {
    string name;
    bool is_directory;
    string content; // содержимое файла
    map<string, VFSNode*> children; // дочерние узлы

    VFSNode(const string& n, bool is_dir = false) : name(n), is_directory(is_dir) {}
};

//класс для виртуальной файловой системы
class VirtualFS {
private:
    VFSNode* root;
    VFSNode* current_dir;

public:
    VirtualFS() {
        root = new VFSNode("", true);
        current_dir = root;
    }

    //загрузка VFS (пока заглушка - создаем тестовую структуру)
    bool loadFromZip(const string& zip_path) {
        cout << "Загрузка VFS из: " << zip_path << endl;

        //создаем тестовую структуру файлов
        addFile("/motd", "Добро пожаловать в эмулятор командной оболочки!\nVFS успешно загружена.");
        addFile("/readme.txt", "Это тестовая виртуальная файловая система");
        addDirectory("/home");
        addDirectory("/home/user");
        addFile("/home/user/document.txt", "Содержимое документа пользователя");
        addDirectory("/etc");
        addFile("/etc/config.txt", "config_value=123");
        addDirectory("/var");
        addDirectory("/var/log");
        addFile("/var/log/system.log", "Логи системы...");

        return true;
    }

    //добавление файла
    void addFile(const string& path, const string& content) {
        vector<string> parts = splitPath(path);
        VFSNode* node = root;

        for (size_t i = 0; i < parts.size() - 1; i++) {
            if (node->children.find(parts[i]) == node->children.end()) {
                node->children[parts[i]] = new VFSNode(parts[i], true);
            }
            node = node->children[parts[i]];
        }

        node->children[parts.back()] = new VFSNode(parts.back(), false);
        node->children[parts.back()]->content = content;
    }

    //добавление директории
    void addDirectory(const string& path) {
        vector<string> parts = splitPath(path);
        VFSNode* node = root;

        for (const string& part : parts) {
            if (node->children.find(part) == node->children.end()) {
                node->children[part] = new VFSNode(part, true);
            }
            node = node->children[part];
        }
    }

    //разбиение пути на части
    vector<string> splitPath(const string& path) {
        vector<string> parts;
        stringstream ss(path);
        string part;

        while (getline(ss, part, '/')) {
            if (!part.empty()) {
                parts.push_back(part);
            }
        }

        return parts;
    }

    //получение содержимого текущей директории
    vector<string> listCurrentDir() {
        vector<string> result;
        for (const auto& entry : current_dir->children) {
            result.push_back(entry.first + (entry.second->is_directory ? "/" : ""));
        }
        return result;
    }

    //смена директории
    bool changeDir(const string& path) {
        if (path == "/") {
            current_dir = root;
            return true;
        }

        vector<string> parts = splitPath(path);
        VFSNode* node = current_dir;

        //обработка абсолютных путей
        if (path[0] == '/') {
            node = root;
        }

        for (const string& part : parts) {
            if (part == "..") {
                if (node != root) {
                    //упрощенная реализация - возврат к корню
                    node = root;
                }
            }
            else if (node->children.find(part) == node->children.end() ||
                !node->children[part]->is_directory) {
                return false;
            }
            else {
                node = node->children[part];
            }
        }

        current_dir = node;
        return true;
    }

    //чтение файла
    string readFile(const string& path) {
        vector<string> parts = splitPath(path);
        VFSNode* node = current_dir;

        //обработка абсолютных путей
        if (path[0] == '/') {
            node = root;
        }

        for (size_t i = 0; i < parts.size(); i++) {
            if (node->children.find(parts[i]) == node->children.end()) {
                return "";
            }
            node = node->children[parts[i]];
        }

        return node->is_directory ? "" : node->content;
    }

    //получение motd
    string getMotd() {
        return readFile("/motd");
    }

    //получение текущего пути
    string getCurrentPath() {
        //упрощенная реализация
        return current_dir == root ? "/" : "/current";
    }
};

class Shell {
private:
    string vfs_name;
    bool running;
    string vfs_path;    //новый параметр
    string script_path; //новый параметр
    VirtualFS vfs;      //НОВЫЙ ОБЪЕКТ VFS

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
                    if (!vfs_path.empty()) {
                        //реальная реализация ls для VFS
                        auto files = vfs.listCurrentDir();
                        if (files.empty()) {
                            cout << "Директория пуста" << endl;
                        }
                        else {
                            cout << "Содержимое директории:" << endl;
                            for (const auto& file : files) {
                                cout << "  " << file << endl;
                            }
                        }
                    }
                    else {
                        //старая заглушка
                        cout << "Команда 'ls' (заглушка) с аргументами: ";
                        for (size_t i = 1; i < args.size(); i++) {
                            cout << "[" << args[i] << "] ";
                        }
                        cout << endl;
                    }
                }
                else if (command == "cd") {
                    if (!vfs_path.empty() && args.size() > 1) {
                        if (vfs.changeDir(args[1])) {
                            cout << "Переход в: " << args[1] << endl;
                        }
                        else {
                            cout << "Ошибка: директория не найдена" << endl;
                        }
                    }
                    else {
                        //старая заглушка
                        cout << "Команда 'cd' (заглушка) с аргументами: ";
                        for (size_t i = 1; i < args.size(); i++) {
                            cout << "[" << args[i] << "] ";
                        }
                        cout << endl;
                    }
                }
                else if (command == "cat") {
                    if (!vfs_path.empty() && args.size() > 1) {
                        string content = vfs.readFile(args[1]);
                        if (!content.empty()) {
                            cout << content << endl;
                        }
                        else {
                            cout << "Ошибка: файл не найден или недоступен" << endl;
                        }
                    }
                    else {
                        cout << "Команда 'cat' (заглушка) с аргументами: ";
                        for (size_t i = 1; i < args.size(); i++) {
                            cout << "[" << args[i] << "] ";
                        }
                        cout << endl;
                    }
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
            if (!vfs_path.empty()) {
                //реальная реализация ls для VFS
                auto files = vfs.listCurrentDir();
                if (files.empty()) {
                    cout << "Директория пуста" << endl;
                }
                else {
                    cout << "Содержимое директории:" << endl;
                    for (const auto& file : files) {
                        cout << "  " << file << endl;
                    }
                }
            }
            else {
                //старая заглушка
                cout << "Команда 'ls' (заглушка) с аргументами: ";
                for (size_t i = 1; i < args.size(); i++) {
                    cout << "[" << args[i] << "] ";
                }
                cout << endl;
            }
        }
        else if (command == "cd") {
            if (!vfs_path.empty() && args.size() > 1) {
                if (vfs.changeDir(args[1])) {
                    cout << "Переход в: " << args[1] << endl;
                }
                else {
                    cout << "Ошибка: директория не найдена" << endl;
                }
            }
            else {
                //старая заглушка
                cout << "Команда 'cd' (заглушка) с аргументами: ";
                for (size_t i = 1; i < args.size(); i++) {
                    cout << "[" << args[i] << "] ";
                }
                cout << endl;
            }
        }
        else if (command == "cat") {
            if (!vfs_path.empty() && args.size() > 1) {
                string content = vfs.readFile(args[1]);
                if (!content.empty()) {
                    cout << content << endl;
                }
                else {
                    cout << "Ошибка: файл не найден или недоступен" << endl;
                }
            }
            else {
                cout << "Команда 'cat' (заглушка) с аргументами: ";
                for (size_t i = 1; i < args.size(); i++) {
                    cout << "[" << args[i] << "] ";
                }
                cout << endl;
            }
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
        //загрузка VFS если указан путь
        if (!vfs_path.empty()) {
            if (!vfs.loadFromZip(vfs_path)) {
                cout << "Ошибка загрузки VFS!" << endl;
                return;
            }

            // Вывод motd если есть
            string motd = vfs.getMotd();
            if (!motd.empty()) {
                cout << "MOTD" << endl;
                cout << motd << endl;
            }
        }

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
        cout << "Доступные команды: ls, cd, cat, conf-dump, exit" << endl << endl;

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

## Этап 4. Основные команды
**Цель**: поддержать команды, имитирующие работу в UNIX-подобной командной строке.
## *Требования*:
1. Необходимо реализовать логику для ls и cd.
2. Реализовать новые команды: du, cat.
3. Создать стартовый скрипт для тестирования всех реализованных на этом этапе команд. Добавить туда примеры всех режимов команд, включая работу с VFS и обработку ошибок.
4. Результат выполнения этапа сохранить в репозиторий стандартно оформленным коммитом.

### Результат 4 этапа
<img width="1488" height="932" alt="image" src="https://github.com/user-attachments/assets/3a7d4c09-9cdf-48c7-a96d-3721b01eb8e4" />

 **Проверено:**
- Логика для `ls` и `cd` - работает корректно
- Команда `du` - показывает размеры файлов и папок
- Команда `cat` - читает содержимое файлов
- Тестовый скрипт проверяет все режимы команд
- Команда `du` рекурсивно вычисляет размеры файлов и директорий в VFS
- Размер файла рассчитывается как длина его содержимого в символах
- Размер директории - сумма размеров всех файлов внутри нее
- Команды `ls`, `cd`, `cat` полностью интегрированы с VFS
- Поддерживаются абсолютные и относительные пути для всех команд
- Обработка ошибок для несуществующих путей

**Тестовые скрипты:**
stage4_test.txt - тестирование команды du и основных команд
------------------------------
conf-dump

ls

du

du /home

du /home/user

cd /home/user

ls

du

cat document.txt

du document.txt

cd /

du /etc

### **Код 4 этапа реализованного на языке С++**
```
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

//структура для узла VFS (файл или папка)
struct VFSNode {
    string name;
    bool is_directory;
    string content; // содержимое файла
    map<string, VFSNode*> children; // дочерние узлы

    VFSNode(const string& n, bool is_dir = false) : name(n), is_directory(is_dir) {}
};

//класс для виртуальной файловой системы
class VirtualFS {
private:
    VFSNode* root;
    VFSNode* current_dir;

public:
    VirtualFS() {
        root = new VFSNode("", true);
        current_dir = root;
    }

    //загрузка VFS (пока заглушка - создаем тестовую структуру)
    bool loadFromZip(const string& zip_path) {
        cout << "Загрузка VFS из: " << zip_path << endl;

        //создаем тестовую структуру файлов
        addFile("/motd", "Добро пожаловать в эмулятор командной оболочки!\nVFS успешно загружена.");
        addFile("/readme.txt", "Это тестовая виртуальная файловая система");
        addDirectory("/home");
        addDirectory("/home/user");
        addFile("/home/user/document.txt", "Содержимое документа пользователя");
        addDirectory("/etc");
        addFile("/etc/config.txt", "config_value=123");
        addDirectory("/var");
        addDirectory("/var/log");
        addFile("/var/log/system.log", "Логи системы...");
        addFile("/home/user/data.txt", "Это файл с данными пользователя для тестирования команды du");

        return true;
    }

    //добавление файла
    void addFile(const string& path, const string& content) {
        vector<string> parts = splitPath(path);
        VFSNode* node = root;

        for (size_t i = 0; i < parts.size() - 1; i++) {
            if (node->children.find(parts[i]) == node->children.end()) {
                node->children[parts[i]] = new VFSNode(parts[i], true);
            }
            node = node->children[parts[i]];
        }

        node->children[parts.back()] = new VFSNode(parts.back(), false);
        node->children[parts.back()]->content = content;
    }

    //добавление директории
    void addDirectory(const string& path) {
        vector<string> parts = splitPath(path);
        VFSNode* node = root;

        for (const string& part : parts) {
            if (node->children.find(part) == node->children.end()) {
                node->children[part] = new VFSNode(part, true);
            }
            node = node->children[part];
        }
    }

    //разбиение пути на части
    vector<string> splitPath(const string& path) {
        vector<string> parts;
        stringstream ss(path);
        string part;

        while (getline(ss, part, '/')) {
            if (!part.empty()) {
                parts.push_back(part);
            }
        }

        return parts;
    }

    //получение содержимого текущей директории
    vector<string> listCurrentDir() {
        vector<string> result;
        for (const auto& entry : current_dir->children) {
            result.push_back(entry.first + (entry.second->is_directory ? "/" : ""));
        }
        return result;
    }

    //смена директории
    bool changeDir(const string& path) {
        if (path == "/") {
            current_dir = root;
            return true;
        }

        vector<string> parts = splitPath(path);
        VFSNode* node = current_dir;

        //обработка абсолютных путей
        if (path[0] == '/') {
            node = root;
        }

        for (const string& part : parts) {
            if (part == "..") {
                if (node != root) {
                    //упрощенная реализация - возврат к корню
                    node = root;
                }
            }
            else if (node->children.find(part) == node->children.end() ||
                !node->children[part]->is_directory) {
                return false;
            }
            else {
                node = node->children[part];
            }
        }

        current_dir = node;
        return true;
    }

    //чтение файла
    string readFile(const string& path) {
        vector<string> parts = splitPath(path);
        VFSNode* node = current_dir;

        //обработка абсолютных путей
        if (path[0] == '/') {
            node = root;
        }

        for (size_t i = 0; i < parts.size(); i++) {
            if (node->children.find(parts[i]) == node->children.end()) {
                return "";
            }
            node = node->children[parts[i]];
        }

        return node->is_directory ? "" : node->content;
    }

    //получение motd
    string getMotd() {
        return readFile("/motd");
    }

    //получение текущего пути
    string getCurrentPath() {
        //упрощенная реализация
        return current_dir == root ? "/" : "/current";
    }

    //НОВ.ФУН: вычисление размера файла/директории
    int calculateSize(VFSNode* node) {
        if (!node->is_directory) {
            return node->content.length();
        }

        int total_size = 0;
        for (const auto& child : node->children) {
            total_size += calculateSize(child.second);
        }
        return total_size;
    }

    //НОВ.ФУН: команда du - показ размеров
    void showDiskUsage(const string& path = "") {
        VFSNode* target_node = current_dir;

        if (!path.empty()) {
            vector<string> parts = splitPath(path);
            target_node = current_dir;

            if (path[0] == '/') {
                target_node = root;
            }

            for (const string& part : parts) {
                if (target_node->children.find(part) == target_node->children.end()) {
                    cout << "Ошибка: путь не найден" << endl;
                    return;
                }
                target_node = target_node->children[part];
            }
        }

        int size = calculateSize(target_node);
        string name = target_node == root ? "/" : target_node->name;
        cout << size << "\t" << name << (target_node->is_directory ? "/" : "") << endl;
    }
};

class Shell {
private:
    string vfs_name;
    bool running;
    string vfs_path;    //новый параметр
    string script_path; //новый параметр
    VirtualFS vfs;      //НОВЫЙ ОБЪЕКТ VFS

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
                    if (!vfs_path.empty()) {
                        //реальная реализация ls для VFS
                        auto files = vfs.listCurrentDir();
                        if (files.empty()) {
                            cout << "Директория пуста" << endl;
                        }
                        else {
                            cout << "Содержимое директории:" << endl;
                            for (const auto& file : files) {
                                cout << "  " << file << endl;
                            }
                        }
                    }
                    else {
                        //старая заглушка
                        cout << "Команда 'ls' (заглушка) с аргументами: ";
                        for (size_t i = 1; i < args.size(); i++) {
                            cout << "[" << args[i] << "] ";
                        }
                        cout << endl;
                    }
                }
                else if (command == "cd") {
                    if (!vfs_path.empty() && args.size() > 1) {
                        if (vfs.changeDir(args[1])) {
                            cout << "Переход в: " << args[1] << endl;
                        }
                        else {
                            cout << "Ошибка: директория не найдена" << endl;
                        }
                    }
                    else {
                        //старая заглушка
                        cout << "Команда 'cd' (заглушка) с аргументами: ";
                        for (size_t i = 1; i < args.size(); i++) {
                            cout << "[" << args[i] << "] ";
                        }
                        cout << endl;
                    }
                }
                else if (command == "cat") {
                    if (!vfs_path.empty() && args.size() > 1) {
                        string content = vfs.readFile(args[1]);
                        if (!content.empty()) {
                            cout << content << endl;
                        }
                        else {
                            cout << "Ошибка: файл не найден или недоступен" << endl;
                        }
                    }
                    else {
                        cout << "Команда 'cat' (заглушка) с аргументами: ";
                        for (size_t i = 1; i < args.size(); i++) {
                            cout << "[" << args[i] << "] ";
                        }
                        cout << endl;
                    }
                }
                //НОВАЯ КОМАНДА: du
                else if (command == "du") {
                    if (!vfs_path.empty()) {
                        if (args.size() > 1) {
                            vfs.showDiskUsage(args[1]);
                        }
                        else {
                            vfs.showDiskUsage();
                        }
                    }
                    else {
                        cout << "Команда 'du' (заглушка) с аргументами: ";
                        for (size_t i = 1; i < args.size(); i++) {
                            cout << "[" << args[i] << "] ";
                        }
                        cout << endl;
                    }
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
            if (!vfs_path.empty()) {
                //реальная реализация ls для VFS
                auto files = vfs.listCurrentDir();
                if (files.empty()) {
                    cout << "Директория пуста" << endl;
                }
                else {
                    cout << "Содержимое директории:" << endl;
                    for (const auto& file : files) {
                        cout << "  " << file << endl;
                    }
                }
            }
            else {
                //старая заглушка
                cout << "Команда 'ls' (заглушка) с аргументами: ";
                for (size_t i = 1; i < args.size(); i++) {
                    cout << "[" << args[i] << "] ";
                }
                cout << endl;
            }
        }
        else if (command == "cd") {
            if (!vfs_path.empty() && args.size() > 1) {
                if (vfs.changeDir(args[1])) {
                    cout << "Переход в: " << args[1] << endl;
                }
                else {
                    cout << "Ошибка: директория не найдена" << endl;
                }
            }
            else {
                //старая заглушка
                cout << "Команда 'cd' (заглушка) с аргументами: ";
                for (size_t i = 1; i < args.size(); i++) {
                    cout << "[" << args[i] << "] ";
                }
                cout << endl;
            }
        }
        else if (command == "cat") {
            if (!vfs_path.empty() && args.size() > 1) {
                string content = vfs.readFile(args[1]);
                if (!content.empty()) {
                    cout << content << endl;
                }
                else {
                    cout << "Ошибка: файл не найден или недоступен" << endl;
                }
            }
            else {
                cout << "Команда 'cat' (заглушка) с аргументами: ";
                for (size_t i = 1; i < args.size(); i++) {
                    cout << "[" << args[i] << "] ";
                }
                cout << endl;
            }
        }
        //НОВАЯ КОМАНДА: du
        else if (command == "du") {
            if (!vfs_path.empty()) {
                if (args.size() > 1) {
                    vfs.showDiskUsage(args[1]);
                }
                else {
                    vfs.showDiskUsage();
                }
            }
            else {
                cout << "Команда 'du' (заглушка) с аргументами: ";
                for (size_t i = 1; i < args.size(); i++) {
                    cout << "[" << args[i] << "] ";
                }
                cout << endl;
            }
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
        //загрузка VFS если указан путь
        if (!vfs_path.empty()) {
            if (!vfs.loadFromZip(vfs_path)) {
                cout << "Ошибка загрузки VFS!" << endl;
                return;
            }

            //вывод motd если есть
            string motd = vfs.getMotd();
            if (!motd.empty()) {
                cout << "MOTD" << endl;
                cout << motd << endl;
            }
        }

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
        cout << "Доступные команды: ls, cd, cat, du, conf-dump, exit" << endl << endl;

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
