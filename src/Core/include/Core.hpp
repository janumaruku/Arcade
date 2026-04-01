#ifndef MYFTP_CORE_HPP
#define MYFTP_CORE_HPP

#include <string>

#include "DlLoader.hpp"
#include "DisplayInterface.hpp"
#include "GameInterface.hpp"

namespace arcade {
namespace core {

class Core {
public:
    explicit Core(const std::string &libraryPath);

private:
    std::unordered_map<std::string, utils::DLLoader> _gameLoaders;
    std::unordered_map<std::string, utils::DLLoader> _displayLoaders;
    std::unordered_map<std::string, std::unique_ptr<game::IGameModule>>
    _gameLibraries;
    std::unordered_map<std::string, std::unique_ptr<display::IDisplayModule>>
    _displayLibraries;
    display::IDisplayModule *_currentDisplay;

    void loadLibrary(const std::string &libraryPath);
    void loadLibraries();
};

} // core
} // arcade

#endif //MYFTP_CORE_HPP
