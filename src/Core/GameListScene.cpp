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
    AScene{core, next, prev}, _tab{widget::Vec2{.x = 0, .y = 0}}
{
    buildWidgets();
    _selectedGame = _gameLibraries.begin();
}

void Core::GameListScene::handleEvent(const widget::Event &event)
{
    switch (event.type) {
    case widget::Event::EventType::CLOSED:
        _core.getCurrentDisplay()->closeWindow();
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

void Core::GameListScene::update()
{
    return;
}

void Core::GameListScene::draw()
{
    _core.getCurrentDisplay()->draw(_tab);
    _core.getCurrentDisplay()->draw(_cursorLeft);
    _core.getCurrentDisplay()->draw(_cursorRight);
    _core.getCurrentDisplay()->draw(_gamesTitle);

    for (const auto &name: _gameLibraries) {
        _core.getCurrentDisplay()->draw(name);
    }
    // if (!_errorMessage.text.empty())
        _core.getCurrentDisplay()->draw(_errorMessage);
}

void Core::GameListScene::buildTab()
{
    _tab.type = widget::WidgetType::RECTANGLE;
    _tab.setSize(widget::Vec2{.x = 70, .y = 15});
    const auto [winWidth, winHeight] = _core.getCurrentDisplay()->
                                             getWindowSize();
    _tab.position.x = (winWidth / 2) - (_tab.getSize().x / 2);
    _tab.position.y = (winHeight / 2) - (_tab.getSize().y / 2) - 5;
}

void Core::GameListScene::buildTitle()
{
    _gamesTitle.type     = widget::WidgetType::TEXT;
    _gamesTitle.text     = "Game libraries";
    _gamesTitle.position = widget::Vec2{
        .x = _tab.position.x + (_tab.getSize().x / 2) - (_gamesTitle.text.
            size() / 2),
        .y = _tab.position.y
    };
}

void Core::GameListScene::buildCursors()
{
    _cursorLeft.type     = widget::WidgetType::TEXT;
    _cursorLeft.text     = "->";
    _cursorLeft.position = widget::Vec2{
        .x = _tab.position.x + 2,
        .y = _tab.position.y + 2
    };
    _cursorRight.type     = widget::WidgetType::TEXT;
    _cursorRight.text     = "<-";
    _cursorRight.position = widget::Vec2{
        .x = _tab.position.x + _tab.getSize().x - 4,
        .y = _tab.position.y + 2
    };
}

void Core::GameListScene::buildList()
{
    // const auto &gameLibraries = _core.getGameLibraries();
    auto yAxis = _tab.position.y + 2;

    auto temp = {std::string{"Game 1"},
                 std::string{"Game 2"},
                 std::string{"Game 3"},
                 std::string{"Game 4"}};

    for (const auto &name: temp/*gameLibraries | std::views::keys*/) {
        _gameLibraries.emplace_back();
        _gameLibraries.back().type     = widget::WidgetType::TEXT;
        _gameLibraries.back().text     = name;
        _gameLibraries.back().position = widget::Vec2{
            .x = (_tab.position.x) + (_tab.getSize().x / 2) - (name.size() / 2),
            .y = yAxis
        };
        yAxis = yAxis + 2;
    }
}

void Core::GameListScene::buildErrorMessage()
{
    _errorMessage.type = widget::WidgetType::TEXT;
    _errorMessage.textColor = widget::Color::RED;
    _errorMessage.position = widget::Vec2{
        .x = _tab.position.x,
        .y = _tab.position.y + _tab.getSize().y + 5
    };
    if (_gameLibraries.empty())
        _errorMessage.text = "Error: No game library available";
}

void Core::GameListScene::buildWidgets()
{
    buildTab();
    buildTitle();
    buildCursors();
    buildList();
    buildErrorMessage();
}

void Core::GameListScene::moveCursorDown()
{
    if (_gameLibraries.empty())
        return;

    ++_selectedGame;

    if (_selectedGame == _gameLibraries.end())
        _selectedGame = _gameLibraries.begin();

    _cursorLeft.position.y  = _selectedGame->position.y;
    _cursorRight.position.y = _selectedGame->position.y;
}

void Core::GameListScene::moveCursorUp()
{
    if (_gameLibraries.empty())
        return;

    if (_selectedGame == _gameLibraries.begin())
        _selectedGame = std::prev(_gameLibraries.end());
    else
        --_selectedGame;

    _cursorLeft.position.y  = _selectedGame->position.y;
    _cursorRight.position.y = _selectedGame->position.y;
}

void Core::GameListScene::handleKeyEvent(const widget::Event &event)
{
    switch (event.key.code) {
    case widget::KeyCode::KEY_Q:
        _core.getCurrentDisplay()->closeWindow();
        break;
    case widget::KeyCode::DOWN:
        moveCursorDown();
        break;
    case widget::KeyCode::UP:
        moveCursorUp();
        break;
    default:
        return;
    }
}

void Core::GameListScene::handleMouseEvent(widget::Event event)
{
    // _errorMessage.text += " hi";
    for (auto elem = _gameLibraries.begin(); elem != _gameLibraries.end(); ++elem) {
        if (event.mouseButton.button == widget::MouseButton::LEFT &&
            event.mouseButton.x >= elem->position.x.getValue() &&
            event.mouseButton.y >= elem->position.y.getValue()) {
            // _errorMessage.
            _selectedGame = elem;
            _cursorLeft.position.y  = _selectedGame->position.y;
            _cursorRight.position.y = _selectedGame->position.y;
            return;
        }
    }
}
}
}
