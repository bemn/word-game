cmake_minimum_required(VERSION 4.0)
project(word_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(word_game
        console/Console.cpp
        console/Console.h

        main.cpp
        list/List.cpp
        list/List.h
)
