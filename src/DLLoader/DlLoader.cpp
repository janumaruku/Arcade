/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** DlLoader
*/

#include "DlLoader.hpp"

#include <dlfcn.h>

namespace utils {
DLLoader::DLLoader(const std::string &path):
    _handle(dlopen(path.c_str(), RTLD_LAZY))
{
    if (_handle == nullptr)
        throw std::runtime_error{"Error: " + std::string{dlerror()}};
}
} // namespace utils
