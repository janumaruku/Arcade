/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** GameScene
*/

#include "Core.hpp"

namespace arcade {
namespace core {

Core::GameScene::GameScene(Core &core, AScene *next, AScene *prev):
    AScene{core, next, prev}
{}

void Core::GameScene::handleEvent(const widget::Event &event)
{
    switch (event.type) {
    case widget::Event::EventType::CLOSED:
        core.getCurrentDisplay()->closeWindow();
        return;
    case widget::Event::EventType::KEY_PRESSED:
        if (event.key.code == widget::KeyCode::ESC) {
            initialized = false;
            goBackToMenu();
            return;
        }
        if (core._currentGame != nullptr)
            core._currentGame->userEvent(event);
        return;
    case widget::Event::EventType::KEY_RELEASED:
    case widget::Event::EventType::MOUSE_BUTTON_PRESSED:
    case widget::Event::EventType::MOUSE_BUTTON_RELEASED:
        if (core._currentGame != nullptr)
            core._currentGame->userEvent(event);
        return;
    default:
        return;
    }
}

void Core::GameScene::update()
{
    if (!initialized)
        initialize();
}

void Core::GameScene::draw()
{
    if (core._currentGame == nullptr)
        return;

    const auto &gameState = core._currentGame->getGameState();

    for (const auto &widget: gameState.widgets) {
        if (widget != nullptr)
            core.getCurrentDisplay()->draw(*widget);
    }

    // for (const auto &sound: gameState.sounds) {
    //     core.getCurrentDisplay()->playSound(sound);
    // }
}

void Core::GameScene::initialize()
{
    applyDisplaySwap();

    if (core._currentGame != nullptr) {
        core.getCurrentDisplay()->loadResource(
            core._currentGame->getResource());
        if (!isStarted) {
            core._currentGame->start();
            isStarted = true;
        }
    }
    initialized = true;
}

void Core::GameScene::applyDisplaySwap() const
{
    if (core._selectedDisplay == nullptr)
        return;
    if (core._currentDisplay == core._selectedDisplay)
        return;

    core._currentDisplay->closeWindow();
    core._currentDisplay = core._selectedDisplay;
    core._currentDisplay->openWindow();
}

void Core::GameScene::goBackToMenu()
{
    if (prevScene != nullptr) {
        initialized = false;
        isStarted = false;
        core._currentScene = prevScene;
    }
}

} // namespace core
} // namespace arcade