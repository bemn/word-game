#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "list/List.h"
#include "input/InputSource.h"

class WordGame {
public:
    void load(InputSource &source);

    bool solve();

    const List &result() const;
    int word_count() const;

private:
    std::vector<std::wstring> words_;
    List result_;

    static wchar_t first_letter(const std::wstring &w);
    static wchar_t last_letter(const std::wstring &w);

    static List build_chain(
        const std::wstring &current,
        std::unordered_multimap<wchar_t, std::wstring> &index
    );
};
