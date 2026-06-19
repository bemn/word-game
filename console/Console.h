#pragma once

#include <sstream>
#include <string>
#include <vector>

class Console {
    static std::wstring trim(const std::wstring &str);

    static std::wstringstream console_stream();

public:
    static std::vector<std::wstring> get_words(std::wstringstream stream = console_stream());

    static int read_int();

    Console &operator<<(const std::string &s);
    Console &operator<<(const char *s);
    Console &operator<<(const char &s);
    Console &operator<<(const std::wstring &ws);
    Console &operator<<(const wchar_t *ws);
    Console &operator<<(const wchar_t &wc);

    Console &operator>>(std::wstring &ws);
};

inline Console wcon;
