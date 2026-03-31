/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** DlLoader
*/

#include "DlLoader.hpp"

#include <dlfcn.h>
#include <iostream>

namespace utils {
DLLoader::~DLLoader()
{
    if (::dlclose(_handle) != 0)
        std::cerr << "Error: " << ::dlerror() << std::endl;
}

void DLLoader::loadLibrary(const std::string &path)
{
    _handle = dlopen(path.c_str(), RTLD_LAZY);

    if (_handle == nullptr)
        throw std::runtime_error{"Error: " + std::string{dlerror()}};
}
} // namespace utils
