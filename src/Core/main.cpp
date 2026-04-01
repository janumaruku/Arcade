/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** main
*/

#include <iostream>

#include "Core.hpp"

int main(const int argc, char *argv[])
{
    if (argc != 2)
        return 84;
    try {
        arcade::core::Core core{argv[1]};
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
