#pragma once

#include <string>
#include <locale>

namespace Encoding {
    inline std::wstring to_wstring(const std::string &s) {
        int n = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
        std::wstring out(n - 1, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, out.data(), n);
        return out;
    }

    inline std::string to_utf8(const std::wstring &ws) {
        int n = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
        std::string out(n - 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, out.data(), n, nullptr, nullptr);
        return out;
    }
};
