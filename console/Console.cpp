#include "Console.h"

#include <codecvt>
#include <locale>
#include <string>
#include <iostream>

std::string Console::to_utf8(const std::wstring &ws) {
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    return conv.to_bytes(ws);
}

std::wstring Console::to_wstring(const std::string &s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    return conv.from_bytes(s);
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
    std::cout << to_utf8(ws);
    return *this;
}

Console &Console::operator<<(const wchar_t *ws) {
    std::cout << to_utf8(ws);
    return *this;
}

Console &Console::operator<<(const wchar_t &wc) {
    const std::wstring ws(1, wc);
    std::cout << to_utf8(ws);
    return *this;
}

Console &Console::operator>>(std::wstring &ws) {
    std::string tmp;
    std::cin >> tmp;
    ws = to_wstring(tmp);
    return *this;
}
