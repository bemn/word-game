#include <unordered_map>

#include "console/Console.h"
#include "list/List.h"

#define FIRST_LETTER(word) word[0]
#define LAST_LETTER(word) (word[word.size() - 1] == L'ь' ? word[word.size() - 2] : word[word.size() - 1])

List build_word_seq(
    const std::wstring &current_word,
    std::unordered_multimap<wchar_t, std::wstring> &first_letters
) {
    List best_list;
    if (first_letters.count(LAST_LETTER(current_word)) == 0) {
        best_list.push(current_word);
        return best_list;
    }

    auto [begin, end] = first_letters.equal_range(LAST_LETTER(current_word));
    std::vector<std::wstring> candidates;
    for (auto it = begin; it != end; ++it) {
        candidates.push_back(it->second);
    }

    for (const auto &word: candidates) {
        auto [b, e] = first_letters.equal_range(FIRST_LETTER(word));
        auto found = e;
        for (auto i = b; i != e; ++i) {
            if (i->second == word) {
                found = i;
                break;
            }
        }
        if (found == e) continue;

        first_letters.erase(found);
        List current_list = build_word_seq(word, first_letters);
        first_letters.insert({FIRST_LETTER(word), word});

        if (current_list.size() > best_list.size()) {
            best_list = current_list;
        }
    }

    best_list.push(current_word);
    return best_list;
}


int main() {
    const std::vector<std::wstring> word_strings = Console::get_words();

    std::unordered_multimap<wchar_t, std::wstring> first_letters;

    for (const auto &w: word_strings) {
        first_letters.insert({FIRST_LETTER(w), w});
    }

    const auto it = first_letters.find(FIRST_LETTER(word_strings[0]));
    const std::wstring word = it->second;
    first_letters.erase(it);
    List best_list = build_word_seq(word, first_letters);

    if (best_list.size() == word_strings.size()
        && FIRST_LETTER(best_list.top()) == LAST_LETTER(best_list.back())) {
        wcon << "Possible solution:\n";
        for (const auto &w: best_list) {
            wcon << w << ' ';
        }
    } else {
        wcon << "Solution not found";
    }
}
