#include "Core.hpp"

#include <iostream>

#include "GameInterface.hpp"

namespace arcade {
namespace core {
Core::Core(const std::string &/*libraryPath*/)
{
    loadLibrary("libraryPath");
}

void Core::loadLibrary(const std::string &libraryPath)
{
    utils::DLLoader loader;

    try {
        loader.loadLibrary(libraryPath);
    } catch (const std::exception &) {
        throw;
    }
    try {
        auto lib = loader.getInstance<display::IDisplayModule>(
            "entryPointDisplay");
        _displayLibraries[lib->getName()] = std::move(lib);
    } catch (const std::exception &) {
        try {
            auto lib = loader.getInstance<game::IGameModule>("entryPointGame");
            _gameLibraries[lib->getName()] = std::move(lib);
        } catch (const std::exception &) {
            std::cerr << "Error: " << libraryPath << " is not a valid library"
                << std::endl;
        }
    }
}
} // core
} // arcade
