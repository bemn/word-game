#include "WordGame.h"

#include <stdexcept>

wchar_t WordGame::first_letter(const std::wstring &w) {
    return w[0];
}

wchar_t WordGame::last_letter(const std::wstring &w) {
    wchar_t last = w[w.size() - 1];
    if (last == L'ь' || last == L'Ь'
        || last == L'ъ' || last == L'Ъ'
        || last == L'ы' || last == L'Ы') {
        return w[w.size() - 2];
    }
    return last;
}

void WordGame::load(InputSource &source) {
    std::vector<std::wstring> words = source.read();
    if (words.empty()) {
        throw std::runtime_error("No words provided.");
    }
    // filter out empty tokens
    words_.clear();
    for (const auto &w: words) {
        if (!w.empty()) {
            words_.push_back(w);
        }
    }
    if (words_.empty()) {
        throw std::runtime_error("No valid words after parsing.");
    }
}

bool WordGame::solve() {
    std::unordered_multimap<wchar_t, std::wstring> index;
    for (const auto &w: words_) {
        index.insert({first_letter(w), w});
    }

    List best;
    for (const auto &w: words_) {
        auto range = index.equal_range(first_letter(w));
        // find and temporarily remove this word from index
        auto found = range.second;
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second == w) {
                found = it;
                break;
            }
        }
        if (found == range.second) continue;

        index.erase(found);
        List chain = build_chain(w, index);
        index.insert({first_letter(w), w});

        if (chain.size() > best.size()) {
            best = chain;
        }
    }

    const bool valid = best.size() == static_cast<int>(words_.size())
                       && first_letter(best.top()) == last_letter(best.back());

    if (valid) {
        result_ = best;
        return true;
    }
    return false;
}

const List &WordGame::result() const {
    return result_;
}

int WordGame::word_count() const {
    return static_cast<int>(words_.size());
}

List WordGame::build_chain(
    const std::wstring &current,
    std::unordered_multimap<wchar_t, std::wstring> &index
) {
    List best;
    if (index.count(last_letter(current)) == 0) {
        best.push(current);
        return best;
    }

    auto range = index.equal_range(last_letter(current));
    std::vector<std::wstring> candidates;
    for (auto it = range.first; it != range.second; ++it) {
        candidates.push_back(it->second);
    }

    for (const auto &word: candidates) {
        auto r = index.equal_range(first_letter(word));
        auto found = r.second;
        for (auto it = r.first; it != r.second; ++it) {
            if (it->second == word) {
                found = it;
                break;
            }
        }
        if (found == r.second) continue;

        index.erase(found);
        List chain = build_chain(word, index);
        index.insert({first_letter(word), word});

        if (chain.size() > best.size()) {
            best = chain;
        }
    }

    best.push(current);
    return best;
}
