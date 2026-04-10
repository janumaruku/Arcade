/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** GameListScene
*/

#include <ranges>

#include "Core.hpp"

namespace arcade {
namespace core {
Core::GameListScene::GameListScene(Core &core, AScene *next, AScene *prev):
    ListMenuScene{core, next, prev}
{
    buildWidgets();
    _selectedLib = _libraries.begin();
}

std::string Core::GameListScene::getTitleText() const
{
    return "Game libraries";
}

std::string Core::GameListScene::getDescriptionText() const
{
    return "Select a game";
}

std::vector<std::string> Core::GameListScene::getItemNames() const
{
    std::vector<std::string> names;
    for (const auto &name: core.getGameLibraries() | std::views::keys) {
        names.emplace_back(name);
    }
    return names;
}

void Core::GameListScene::onSelect() const
{
    if (_selectedLib == _libraries.end())
        return;
    const auto itt =
        std::ranges::find_if(core._gameLibraries, [this](const auto &elem) {
            return _selectedLib->text == elem.first;
        });
    if (itt != core._gameLibraries.end()) {
        core._currentGame = itt->second.get();
        core.resetGameSceneState();
    }
}
}
}
