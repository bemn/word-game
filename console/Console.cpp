#include "Console.h"

#include <string>
#include <iostream>
#include "encoding/Encoding.h"

std::wstring Console::trim(const std::wstring &str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        ++start;
    }

    auto end = str.end();
    do {
        --end;
    } while (end != start && std::isspace(*end));

    if (start > end) {
        return L"";
    }

    return {start, end + 1};
}

std::wstringstream Console::console_stream() {
    std::string line;
    std::getline(std::cin, line);
    return std::wstringstream(trim(Encoding::to_wstring(line)));
}

std::vector<std::wstring> Console::get_words(std::wstringstream stream) {
    std::vector<std::wstring> result;
    while (!stream.eof()) {
        std::wstring word;
        stream >> word;
        result.push_back(word);
    }
    if (stream.fail()) {
        return {};
    }
    return result;
}

Console &Console::operator<<(const std::string &s) {
    std::cout << s;
    return *this;
}

Console &Console::operator<<(const char *s) {
    std::cout << s;
    return *this;
}

Console &Console::operator<<(const char &s) {
    std::cout << s;
    return *this;
}

Console &Console::operator<<(const std::wstring &ws) {
    std::cout << Encoding::to_utf8(ws);
    return *this;
}

Console &Console::operator<<(const wchar_t *ws) {
    std::cout << Encoding::to_utf8(ws);
    return *this;
}

Console &Console::operator<<(const wchar_t &wc) {
    std::cout << Encoding::to_utf8(std::wstring(1, wc));
    return *this;
}

Console &Console::operator>>(std::wstring &ws) {
    std::string tmp;
    std::cin >> tmp;
    ws = Encoding::to_wstring(tmp);
    return *this;
}

int Console::read_int() {
    std::string line;
    std::getline(std::cin, line);
    try {
        return std::stoi(line);
    } catch (...) {
        return -1;
    }
}
