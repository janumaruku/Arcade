/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** test_lib
*/

#include <iostream>

void __attribute__((constructor)) first() {
    std::cout << "Building the dynamic library" << std::endl;
}

void __attribute__((destructor)) last()
{
    std::cout << "Destructing the dynamic library" << std::endl;
}

// extern "C" {
    void myEntryPoint()
    {
        std::cout << "Entry Point" << std::endl;
    }
// }
