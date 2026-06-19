#include "Menu.h"

#include <iostream>
#include <sstream>

#include "console/Console.h"

// Item
Item::Item(string name, std::function<void()> func)
    : func_(std::move(func)) {
    name_ = "";
    for (int i = 0; i < name.length(); i++) {
        const char c = name[i];
        if (!name_.empty() && name_[name_.length() - 1] != ' ' && c == '_') {
            name_ += ' ';
        }
        if (c != '_') {
            name_ += c;
        }
    }
    if (!name_.empty()) {
        name_[0] = static_cast<char>(std::toupper(name_[0]));
    }
}

const string &Item::get_name() const {
    return name_;
}

void Item::execute() const {
    func_();
}

// Menu
Menu::Menu(string title, string desc, vector<Item> items, string exit)
    : title_(std::move(title)),
      desc_(std::move(desc)),
      items_(std::move(items)),
      exit_(std::move(exit)) {
    last_choice_ = 0;
}

Menu::Menu(string title, vector<Item> items, string exit)
    : title_(std::move(title)),
      items_(std::move(items)),
      exit_(std::move(exit)) {
    last_choice_ = 0;
}

string &Menu::get_title() {
    return title_;
}

void Menu::wait_for_input() {
    std::cout << "\nPress Enter to continue...\n";
    string throwaway;
    std::getline(std::cin, throwaway);
}

void Menu::display() const {
    std::cout << " --- " << title_ << " --- \n";
    if (!desc_.empty()) {
        std::cout << desc_ << "\n";
    }
    std::cout << '\n';
    for (int i = 0; i < items_.size(); i++) {
        std::cout << i + 1 << ". " << items_[i].get_name() <<
                (last_choice_ == i + 1 ? " <-\n" : "\n");
    }
    std::cout << "0. " << exit_ << '\n';
}

void Menu::run() {
    last_choice_ = 0;
    display();
    do {
        std::cout << "> ";
        int choice = Console::read_int();
        if (choice == 0) {
            return;
        }
        if (choice < 1 || choice > items_.size()) {
            std::cout << "Please pick a choice between 0 and "
                    << items_.size() << '\n';
            continue;
        }
        items_[choice - 1].execute();
        last_choice_ = choice;
        display();
    } while (true);
}

Item Menu::as_item() {
    return {
        title_,
        [this]() { this->run(); }
    };
}
