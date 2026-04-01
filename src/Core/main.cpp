/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** main
*/

#include <iostream>

#include "Core.hpp"

int main()
{
    std::cout << "Hello World!" << std::endl;

    try {
        arcade::core::Core core{"./libs/arcade_ncurses.so"};
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
