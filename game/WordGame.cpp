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
    words_.clear();
    for (const auto &w: words) {
        std::wstring filtered;
        for (wchar_t c: w) {
            if ((c >= L'a' && c <= L'z') || (c >= L'а' && c <= L'я') || c == L'ё') {
                filtered += c;
            } else if ((c >= L'A' && c <= L'Z')) {
                filtered += c + (L'a' - L'A');
            } else if ((c >= L'А' && c <= L'Я') || c == L'Ё') {
                filtered += (c == L'Ё') ? L'ё' : (c + (L'а' - L'А'));
            }
        }
        if (!filtered.empty()) {
            words_.push_back(filtered);
        }
    }
    if (words_.empty()) {
        throw std::runtime_error("No valid words after parsing.");
    }
}

bool WordGame::solve() {
    // индекс - словарь
    // ключ: буква -> значение: все слова на эту букву
    std::unordered_multimap<wchar_t, std::wstring> index;
    for (const auto &w: words_) {
        index.insert({first_letter(w), w});
    }

    // перебираем каждое слово как стартовое
    List best;
    for (const auto &w: words_) {
        // ищем это слово в индексе...
        auto range = index.equal_range(first_letter(w));
        auto found = range.second;
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second == w) {
                found = it;
                break;
            }
        }
        if (found == range.second) continue;

        // ...и временно удаляем его из индекса
        index.erase(found);
        // запускаем построение цепочки с этого слова
        List chain = build_chain(w, index);
        // после построения цепочки возвращаем слово обратно в индекс
        index.insert({first_letter(w), w});

        // находим самую длинную цепочку
        if (chain.size() > best.size()) {
            best = chain;
        }
    }

    // проверяем цепочку на валидность:
    // 1. все слова должны быть использованы
    // 2. первая буква первого слова = последняя буква последнего слова
    const bool valid = best.size() == static_cast<int>(words_.size())
                       && first_letter(best.top()) == last_letter(best.back());

    // если валидна - true и пишем в результат, иначе false
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

    // если нет слов начинающихся на последнюю букву текущего слова -
    // возвращаем цепочку из одного слова
    if (index.count(last_letter(current)) == 0) {
        best.push(current);
        return best;
    }

    // перебираем всех кандидатов начинающихся на последнюю букву текущего слова
    auto range = index.equal_range(last_letter(current));
    std::vector<std::wstring> candidates;
    for (auto it = range.first; it != range.second; ++it) {
        candidates.push_back(it->second);
    }

    // проход по всем кандидатам
    for (const auto &word: candidates) {
        // ищем этого кандидата в индексе...
        auto r = index.equal_range(first_letter(word));
        auto found = r.second;
        for (auto it = r.first; it != r.second; ++it) {
            if (it->second == word) {
                found = it;
                break;
            }
        }
        if (found == r.second) continue;

        // ...и временно удаляем его из индекса
        index.erase(found);
        // рекурсивно строим цепочку как если бы строили начиная из кандидата
        List chain = build_chain(word, index);
        // восстанавливаем кандидата обратно в индекс
        index.insert({first_letter(word), word});

        // ищем самую длинную цепочку
        if (chain.size() > best.size()) {
            best = chain;
        }
    }

    // добавляем текущее слово в начало полученной цепочки
    best.push(current);
    return best;
}
