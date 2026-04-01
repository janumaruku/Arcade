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

    DLLoader(const DLLoader &loader) = default;

    DLLoader(DLLoader &&loader) noexcept;

    DLLoader &operator=(DLLoader &&loader) noexcept;

    ~DLLoader();

    void loadLibrary(const std::string &path);

    template <typename Object>
    std::unique_ptr<Object> getInstance(const std::string &symbol)
    {
        void *result = dlsym(_handle, symbol.c_str());

        if (result == nullptr)
            throw std::runtime_error{symbol + ": " + std::string{dlerror()}};

        using EntryPoint = Object *(*)();
        auto entryPoint  = reinterpret_cast<EntryPoint>(result);

        Object *object = entryPoint();
        std::unique_ptr<Object> instance{object};
        return instance;
    }

    template <typename FuncType>
    FuncType getSymbol(const std::string &symbol)
    {
        void *result = dlsym(_handle, symbol.c_str());

        if (result == nullptr)
            throw std::runtime_error{symbol + ": " + std::string{dlerror()}};

        return reinterpret_cast<FuncType>(result);
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
