#pragma once

#include <functional>
#include <vector>
#include <string>

using std::string;
using std::vector;

#define MAKE_ITEM(func) Item(#func, []() { func(); Menu::wait_for_input(); })

class Item {
    string name_;
    std::function<void()> func_;

public:
    Item() = default;

    Item(string name, std::function<void()> func);

    const string &get_name() const;

    void execute() const;
};

class Menu {
    string title_;
    string desc_;
    vector<Item> items_;
    string exit_;
    int last_choice_;

    void display() const;

public:
    Menu(string title, string desc, vector<Item> items, string exit);

    Menu(string title, vector<Item> items, string exit);

    string &get_title();

    static void wait_for_input();

    void run();

    Item as_item();
};
