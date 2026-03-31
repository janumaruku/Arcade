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

class DLLoader {
public:
    DLLoader() = default;

    ~DLLoader();

    void loadLibrary(const std::string &path);

    template <typename Object>
    std::unique_ptr<Object> getInstance(const std::string &symbol)
    {
        void *result = dlsym(_handle, symbol.c_str());

        if (result == nullptr)
            throw std::runtime_error{symbol + ": " + std::string{dlerror()}};

        using EntryPoint = Object *(*)();
        auto entryPoint  = dynamic_cast<EntryPoint>(result);
        if (entryPoint == nullptr)
            throw std::runtime_error{"Incorrect type in template parameter."};

        std::unique_ptr<Object> instance{entryPoint(), delFunc};
        return instance;
    }

    template <typename FuncType>
    FuncType getSymbol(const std::string &symbol)
    {
        void *result = dlsym(_handle, symbol.c_str());

        if (result == nullptr)
            throw std::runtime_error{symbol + ": " + std::string{dlerror()}};

        auto func = dynamic_cast<FuncType>(result);
        if (func == nullptr)
            throw std::runtime_error{"Incorrect type in template parameter."};

        return func;
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
