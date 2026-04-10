/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** DisplayListScene
*/

#include <ranges>

#include "Core.hpp"

namespace arcade {
namespace core {

Core::DisplayListScene::DisplayListScene(
    Core &core, AScene *next, AScene *prev):
    ListMenuScene{core, next, prev}
{
    buildWidgets();
    _selectedLib = _libraries.begin();
}

std::string Core::DisplayListScene::getTitleText() const
{
    return "Display libraries";
}

std::string Core::DisplayListScene::getDescriptionText() const
{
    return "Select a display library";
}

std::vector<std::string> Core::DisplayListScene::getItemNames() const
{
    std::vector<std::string> names;
    for (const auto &name: core.getDisplayLibraries() | std::views::keys) {
        names.emplace_back(name);
    }
    return names;
}

void Core::DisplayListScene::onSelect() const
{
    if (_selectedLib == _libraries.end())
        return;
    const auto itt =
        std::ranges::find_if(core._displayLibraries, [this](const auto &elem) {
            return _selectedLib->text == elem.first;
        });
    if (itt != core._displayLibraries.end()) {
        core._selectedDisplay = itt->second.get();
        core.resetGameSceneState();
    }
}

} // namespace core
} // namespace arcade
