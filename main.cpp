#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "console/Console.h"

struct WordNode {
    std::wstring word;
    wchar_t start;
    wchar_t end;

    explicit WordNode(std::wstring w) : word(std::move(w)) {
        start = word[0];
        end = word[word.length() - 1];
        if (end == L'ь') {
            end = word[word.length() - 2];
        }
    }
};

using WordNodeUnique = std::unique_ptr<WordNode>;
using WordSet = std::unordered_set<WordNode *>;
using WordMap = std::unordered_map<wchar_t, WordSet>;

std::vector<WordNode *> build_game(
    std::vector<WordNode *> current_list,
    WordMap starts
) {
    const WordNode *last = current_list[current_list.size() - 1];
    std::vector<WordNode *> best_list = current_list;
    if (starts.count(last->end) == 0 || starts.at(last->end).empty()) {
        return best_list;
    }
    for (auto word: starts.at(last->end)) {
        std::vector<WordNode *> temp_vec = current_list;
        WordMap temp_map = starts;
        temp_map.at(last->end).erase(word);

        temp_vec.push_back(word);
        std::vector<WordNode *> list = build_game(std::move(temp_vec), std::move(temp_map));
        if (list.size() > best_list.size()) {
            best_list = list;
        }
    }
    return best_list;
}

int main() {
    const std::vector<std::wstring> word_strings = Console::get_words();
    std::vector<WordNodeUnique> words;
    WordMap words_start;
    for (const auto &word: word_strings) {
        auto node = std::make_unique<WordNode>(word);
        words_start[node->start].insert(node.get());
        words.push_back(std::move(node));
    }

    std::vector<WordNode *> best_list;
    for (auto &node: words) {
        WordMap starts = words_start;
        starts[node->start].erase(node.get());
        std::vector<WordNode *> cur = build_game(
            {node.get()},
            starts
        );
        if (cur.size() > best_list.size()) {
            best_list = cur;
        }
    }

    if (best_list.size() == word_strings.size()) {
        wcon << "Possible solution:\n";
        for (const auto word: best_list) {
            wcon << word->word << ' ';
        }
    } else {
        wcon << "Possible solution not found";
    }
}
