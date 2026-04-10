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
    _currentDisplay  = _displayLibraries.begin()->second.get();
    _selectedDisplay = _displayLibraries.begin()->second.get();
    loadLibraries();

    _currentDisplay->openWindow(widget::Vec2{.x = 100, .y = 40});
    buildScenes();
}
void Core::run() const
{
    widget::Event event;

    while (_currentDisplay->isOpen()) {
        while (_currentDisplay->pollEvent(event)) {
            _currentScene->handleEvent(event);
        }

        _currentDisplay->clear(widget::Color::TRANSPARENT);
        _currentScene->update();
        _currentScene->draw();
        _currentDisplay->display();
    }
}

void Core::buildScenes()
{
    auto nameEntry = std::make_unique<NameEntryScene>(*this);
    auto game =
        std::make_unique<GameListScene>(*this, nullptr, nameEntry.get());
    auto disp = std::make_unique<DisplayListScene>(*this, nullptr, game.get());
    auto gameScene = std::make_unique<GameScene>(*this, nullptr, disp.get());
    nameEntry->nextScene = game.get();
    game->nextScene      = disp.get();
    disp->nextScene      = gameScene.get();
    _currentScene        = nameEntry.get();
    _scenes.emplace_back(std::move(nameEntry));
    _scenes.emplace_back(std::move(game));
    _scenes.emplace_back(std::move(disp));
    _scenes.emplace_back(std::move(gameScene));
}

void Core::resetGameSceneState() const noexcept
{
    for (const auto &scene: _scenes) {
        if (auto *gameScene = dynamic_cast<GameScene *>(scene.get())) {
            gameScene->initialized = false;
            gameScene->isStarted   = false;
            return;
        }
    }
}

const Core::GameLibrariesMap &Core::getGameLibraries() const noexcept
{
    return _gameLibraries;
}

const Core::DisplayLibrariesMap &Core::getDisplayLibraries() const noexcept
{
    return _displayLibraries;
}
void Core::loadLibrary(const std::string &libraryPath)
{
    utils::DLLoader loader;
    loader.loadLibrary(libraryPath);

    try {
        auto lib =
            loader.getInstance<display::IDisplayModule>("entryPointDisplay");

        if (_displayLibraries.contains(lib->getName()))
            return;
        _displayLoaders[lib->getName()]   = std::move(loader);
        _displayLibraries[lib->getName()] = std::move(lib);
    } catch (const std::exception &) {
        try {
            auto lib = loader.getInstance<game::IGameModule>("entryPointGame");
            _gameLoaders[lib->getName()]   = std::move(loader);
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

display::IDisplayModule *Core::getCurrentDisplay() const noexcept
{
    return _currentDisplay;
}
} // namespace core
} // namespace arcade
