#include "Core.hpp"

#include <filesystem>
#include <iostream>

#include "GameInterface.hpp"

namespace fs = std::filesystem;

namespace arcade {
namespace core {
Core::Core(const std::string &libraryPath)
{
    loadLibrary(libraryPath);
    _currentDisplay = _displayLibraries.begin()->second.get();
    loadLibraries();
}

void Core::loadLibrary(const std::string &libraryPath)
{
    utils::DLLoader loader;
    loader.loadLibrary(libraryPath);

    try {
        auto lib = loader.getInstance<display::IDisplayModule>(
            "entryPointDisplay");

        if (_displayLibraries.contains(lib->getName()))
            return;
        _displayLoaders[lib->getName()]   = std::move(loader);
        _displayLibraries[lib->getName()] = std::move(lib);
    } catch (const std::exception &) {
        try {
            auto lib = loader.getInstance<game::IGameModule>("entryPointGame");
            _gameLoaders[lib->getName()] = std::move(loader);
            _gameLibraries[lib->getName()] = std::move(lib);
        } catch (const std::exception &) {
            throw std::runtime_error{
                "Error: " + libraryPath + " is not a valid library"};
        }
    }
}

void Core::loadLibraries()
{
    const fs::path libsDirectory{"./libs"};

    if (!fs::is_directory(libsDirectory))
        throw std::runtime_error{"Error: libs directory not found"};

    for (const auto &entry: fs::directory_iterator(libsDirectory)) {
        try {
            loadLibrary(entry.path().string());
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}
} // core
} // arcade
