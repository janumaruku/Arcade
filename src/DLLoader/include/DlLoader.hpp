/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** DlLoader
*/

#ifndef MYFTP_DLLOADER_HPP
#define MYFTP_DLLOADER_HPP

#include <dlfcn.h>
#include <memory>
#include <string>

namespace utils {

//template <typename Object>
class DLLoader {
public:
    DLLoader() = default;

    explicit DLLoader(const std::string &path);

    template <typename Object>
    std::unique_ptr<Object> getInstance(const std::string &symbol)
    {
        void *result = dlsym(_handle, symbol.c_str());

        if (result == nullptr)
            throw std::runtime_error{symbol + ": " + std::string{dlerror()}};

        using EntryPoint      = Object *(*)();
        EntryPoint entryPoint = entryPoint = dynamic_cast<EntryPoint>(result);
        if (entryPoint == nullptr)
            throw std::runtime_error{"Incorrect type in template parameter."};

        std::unique_ptr<Object> instance{entryPoint(), delFunc};

        return nullptr;
    }

private:
    void *_handle = nullptr;

    template <typename Object>
    static void delFunc(Object *ptr)
    {
        delete ptr;
    }
};

} // namespace utils

#endif // MYFTP_DLLOADER_HPP
