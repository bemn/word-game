#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>

#include "console/Console.h"
#include "encoding/Encoding.h"
#include "menu/Menu.h"
#include "game/WordGame.h"
#include "input/ConsoleInput.h"
#include "input/FileInput.h"

static List last_result;
static bool has_result = false;

static void run_game(InputSource &source) {
    try {
        WordGame game;
        game.load(source);

        wcon << "Loaded " << std::to_string(game.word_count()) << " words.\n";
        wcon << "Solving...\n";

        if (game.solve()) {
            wcon << "Solution:\n";
            for (const auto &w: game.result()) {
                wcon << w << L' ';
            }
            wcon << "\n";
            last_result = game.result();
            has_result = true;
        } else {
            wcon << "No solution exists for the given words.\n";
        }
    } catch (const std::runtime_error &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

static void run_from_console() {
    ConsoleInput src;
    run_game(src);
}

static void run_from_file() {
    std::cout << "Enter file path: ";
    std::string path;
    std::getline(std::cin, path);
    try {
        FileInput src(path);
        run_game(src);
    } catch (const std::runtime_error &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

static void save_result() {
    if (!has_result) {
        std::cout << "No result to save yet. Run the game first.\n";
        return;
    }
    std::cout << "Enter output file path: ";
    std::string path;
    std::getline(std::cin, path);
    try {
        std::ofstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing: " + path);
        }
        for (const auto &w: last_result) {
            file << Encoding::to_utf8(w) << ' ';
        }
        file << '\n';
        std::cout << "Saved to " << path << "\n";
    } catch (const std::runtime_error &e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

int main() {
    Menu menu(
        "Word Chain Game",
        {
            Item("From console", []() {
                run_from_console();
                Menu::wait_for_input();
            }),
            Item("From file", []() {
                run_from_file();
                Menu::wait_for_input();
            }),
            Item("Save last result", []() {
                save_result();
                Menu::wait_for_input();
            }),
        },
        "Exit"
    );
    menu.run();
    return 0;
}
