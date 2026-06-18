#pragma once

#include <string>

class Console {
    static std::string to_utf8(const std::wstring &ws);

    static std::wstring to_wstring(const std::string &s);

public:
    Console &operator<<(const std::string &s);

    Console &operator<<(const char *s);

    Console &operator<<(const char &s);

    Console &operator<<(const std::wstring &ws);

    Console &operator<<(const wchar_t *ws);

    Console &operator<<(const wchar_t &wc);

    Console &operator>>(std::wstring &ws);
};

inline Console wcon;
