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
DLLoader::DLLoader(DLLoader &&loader) noexcept: _handle{loader._handle}
{
    loader._handle = nullptr;
}

DLLoader &DLLoader::operator=(DLLoader &&loader) noexcept
{
    if (this != &loader) {
        if (_handle != nullptr)
            ::dlclose(_handle);
        _handle = loader._handle;
        loader._handle = nullptr;
    }
    return *this;
}

DLLoader::~DLLoader()
{
    if (_handle == nullptr)
        return;
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
