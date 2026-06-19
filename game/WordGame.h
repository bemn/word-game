#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "list/List.h"
#include "input/InputSource.h"

class WordGame {
public:
    // Loads words from source. Throws std::runtime_error if result is empty.
    void load(InputSource &source);

    // Attempts to solve. Returns false if no solution exists.
    bool solve();

    const List &result() const;
    int word_count() const;

private:
    std::vector<std::wstring> words_;
    List result_;

    static wchar_t first_letter(const std::wstring &w);
    static wchar_t last_letter(const std::wstring &w);

    List build_chain(
        const std::wstring &current,
        std::unordered_multimap<wchar_t, std::wstring> &index
    );
};
