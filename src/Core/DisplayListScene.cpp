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
    AScene{core, next, prev}, _tab{widget::Vec2{.x = 0, .y = 0}}
{
    buildWidgets();
    _selectedLib = _libraries.begin();
}

void Core::DisplayListScene::handleEvent(const widget::Event &event)
{
    switch (event.type) {
    case widget::Event::EventType::CLOSED:
        core.getCurrentDisplay()->closeWindow();
        return;
    case widget::Event::EventType::KEY_PRESSED:
        handleKeyEvent(event);
        return;
    case widget::Event::EventType::MOUSE_BUTTON_PRESSED:
        handleMouseEvent(event);
        return;
    default:
        return;
    }
}

void Core::DisplayListScene::update()
{
    return;
}

void Core::DisplayListScene::draw()
{
    core.getCurrentDisplay()->draw(_tab);
    core.getCurrentDisplay()->draw(_cursorLeft);
    core.getCurrentDisplay()->draw(_cursorRight);
    core.getCurrentDisplay()->draw(_title);

    for (const auto &name: _libraries) {
        core.getCurrentDisplay()->draw(name);
    }
    core.getCurrentDisplay()->draw(_descriptionMessage);
    if (!_errorMessage.text.empty())
        core.getCurrentDisplay()->draw(_errorMessage);
}

void Core::DisplayListScene::buildTab()
{
    _tab.type = widget::WidgetType::RECTANGLE;
    _tab.setSize(widget::Vec2{.x = 70, .y = 15});
    const auto [winWidth, winHeight] =
        core.getCurrentDisplay()->getWindowSize();
    _tab.position.x = (winWidth / 2) - (_tab.getSize().x / 2);
    _tab.position.y = (winHeight / 2) - (_tab.getSize().y / 2) - 5;
}

void Core::DisplayListScene::buildTitle()
{
    _title.type     = widget::WidgetType::TEXT;
    _title.text     = "Display libraries";
    _title.position = widget::Vec2{.x = _tab.position.x +
            (_tab.getSize().x / 2) - (_title.text.size() / 2),
        .y = _tab.position.y};
}

void Core::DisplayListScene::buildCursors()
{
    _cursorLeft.type = widget::WidgetType::TEXT;
    _cursorLeft.text = "->";
    _cursorLeft.position =
        widget::Vec2{.x = _tab.position.x + 2, .y = _tab.position.y + 2};
    _cursorRight.type     = widget::WidgetType::TEXT;
    _cursorRight.text     = "<-";
    _cursorRight.position = widget::Vec2{
        .x = _tab.position.x + _tab.getSize().x - 4, .y = _tab.position.y + 2};
}

void Core::DisplayListScene::buildList()
{
    const auto &gameLibraries = core._displayLibraries;
    auto yAxis = _tab.position.y + 2;

    for (const auto &name: gameLibraries | std::views::keys) {
        _libraries.emplace_back();
        _libraries.back().type     = widget::WidgetType::TEXT;
        _libraries.back().text     = name;
        _libraries.back().position = widget::Vec2{
            .x = (_tab.position.x) + (_tab.getSize().x / 2) - (name.size() / 2),
            .y = yAxis};
        yAxis = yAxis + 2;
    }
}

void Core::DisplayListScene::buildErrorMessage()
{
    _descriptionMessage.type      = widget::WidgetType::TEXT;
    _descriptionMessage.textColor = widget::Color::GREEN;
    _descriptionMessage.position  = widget::Vec2{
         .x = _tab.position.x, .y = _tab.position.y + _tab.getSize().y + 5};
    _errorMessage.type       = widget::WidgetType::TEXT;
    _descriptionMessage.text = "Select a display library";
    _errorMessage.textColor  = widget::Color::RED;
    _errorMessage.position   = widget::Vec2{
          .x = _tab.position.x, .y = _descriptionMessage.position.y + 2};
    if (_libraries.empty())
        _errorMessage.text = "Error: No library available";
}

void Core::DisplayListScene::buildWidgets()
{
    buildTab();
    buildTitle();
    buildCursors();
    buildList();
    buildErrorMessage();
}

void Core::DisplayListScene::moveCursorDown()
{
    if (_libraries.empty())
        return;

    ++_selectedLib;

    if (_selectedLib == _libraries.end())
        _selectedLib = _libraries.begin();

    _cursorLeft.position.y  = _selectedLib->position.y;
    _cursorRight.position.y = _selectedLib->position.y;
}

void Core::DisplayListScene::moveCursorUp()
{
    if (_libraries.empty())
        return;

    if (_selectedLib == _libraries.begin())
        _selectedLib = std::prev(_libraries.end());
    else
        --_selectedLib;

    _cursorLeft.position.y  = _selectedLib->position.y;
    _cursorRight.position.y = _selectedLib->position.y;
}
void Core::DisplayListScene::goToNextScene() const
{
    if (nextScene != nullptr) {
        core._currentScene = nextScene;
    }
}
void Core::DisplayListScene::goToPreviousScene() const
{
    if (prevScene != nullptr)
        core._currentScene = prevScene;
}

void Core::DisplayListScene::handleKeyEvent(const widget::Event &event)
{
    switch (event.key.code) {
    case widget::KeyCode::KEY_Q:
        core.getCurrentDisplay()->closeWindow();
        break;
    case widget::KeyCode::DOWN:
        moveCursorDown();
        break;
    case widget::KeyCode::UP:
        moveCursorUp();
        break;
    case widget::KeyCode::ENTER:
    case widget::KeyCode::KEY_N:
    case widget::KeyCode::RIGHT:
        goToNextScene();
        break;
    case widget::KeyCode::KEY_P:
    case widget::KeyCode::LEFT:
        goToPreviousScene();
        break;
    default:
        break;
    }
}

void Core::DisplayListScene::handleMouseEvent(const widget::Event &event)
{
    if (event.mouseButton.button != widget::MouseButton::LEFT)
        return;

    for (auto elem = _libraries.begin(); elem != _libraries.end(); ++elem) {
        const std::size_t eventX = event.mouseButton.x;
        const std::size_t eventY = event.mouseButton.y;
        const std::size_t minX   = _cursorLeft.position.x.getValue();
        const std::size_t maxX =
            _cursorRight.position.x.getValue() + _cursorLeft.text.size();
        const std::size_t yAxis = elem->position.y.getValue();
        if (eventX >= minX && eventX < maxX && eventY == yAxis) {
            _selectedLib            = elem;
            _cursorLeft.position.y  = _selectedLib->position.y;
            _cursorRight.position.y = _selectedLib->position.y;
            return;
        }
    }
}
} // namespace core
} // namespace arcade
