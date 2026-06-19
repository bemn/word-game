cmake_minimum_required(VERSION 3.10)
project(word_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(word_game
        console/Console.cpp
        console/Console.h

        menu/Menu.cpp
        menu/Menu.h

        list/List.cpp
        list/List.h

        input/InputSource.h
        input/ConsoleInput.h
        input/FileInput.h

        game/WordGame.cpp
        game/WordGame.h

        encoding/Encoding.h

        main.cpp
)
