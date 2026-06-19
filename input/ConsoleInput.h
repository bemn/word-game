#pragma once

#include <iostream>
#include "InputSource.h"
#include "console/Console.h"

class ConsoleInput : public InputSource {
public:
    std::vector<std::wstring> read() override {
        std::cout << "Enter words on one line separated by spaces:\n> ";
        return Console::get_words();
    }

    std::string description() const override {
        return "Console";
    }
};
