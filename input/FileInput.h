#pragma once

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "InputSource.h"
#include "encoding/Encoding.h"
#include "console/Console.h"

class FileInput : public InputSource {
public:
    explicit FileInput(std::string path) : path_(std::move(path)) {}

    std::vector<std::wstring> read() override {
        std::ifstream file(path_);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + path_);
        }
        std::string line, all;
        while (std::getline(file, line)) {
            if (!all.empty()) all += ' ';
            all += line;
        }
        std::wstringstream wss(Encoding::to_wstring(all));
        return Console::get_words(std::move(wss));
    }

    std::string description() const override {
        return "File: " + path_;
    }

private:
    std::string path_;
};
