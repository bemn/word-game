#pragma once

#include <string>
#include <codecvt>
#include <locale>

class Encoding {
public:
    static std::string to_utf8(const std::wstring &ws) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.to_bytes(ws);
    }

    static std::wstring to_wstring(const std::string &s) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        return conv.from_bytes(s);
    }
};