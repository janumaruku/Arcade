/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** ListMenuScene
*/

#include <ranges>

#include "Core.hpp"

namespace arcade {
namespace core {

Core::ListMenuScene::ListMenuScene(Core &core, AScene *next, AScene *prev):
    AScene{core, next, prev},
    _tab{widget::Vec2{.x = 0, .y = 0}},
    _prevButton{widget::Vec2{.x = 0, .y = 0}},
    _nextButton{widget::Vec2{.x = 0, .y = 0}}
{}

void Core::ListMenuScene::handleEvent(const widget::Event &event)
{
    switch (event.type) {
    case widget::Event::EventType::CLOSED:
        core.getCurrentDisplay()->closeWindow();
        return;
    case widget::Event::EventType::KEY_PRESSED:
        handleKeyEvent(event);
        return;
    case widget::Event::EventType::MOUSE_BUTTON_RELEASED:
        handleMouseEvent(event);
        return;
    default:
        return;
    }
}

void Core::ListMenuScene::update()
{}

void Core::ListMenuScene::draw()
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

    core.getCurrentDisplay()->draw(_keyHelpText);
    core.getCurrentDisplay()->draw(_prevButton);
    core.getCurrentDisplay()->draw(_prevButtonText);
    core.getCurrentDisplay()->draw(_nextButton);
    core.getCurrentDisplay()->draw(_nextButtonText);
}

void Core::ListMenuScene::buildTab()
{
    _tab.type = widget::WidgetType::RECTANGLE;
    _tab.setSize(widget::Vec2{.x = 50, .y = 15});
    const auto [winWidth, winHeight] =
        core.getCurrentDisplay()->getWindowSize();
    _tab.position.x = (winWidth / 2) - (_tab.getSize().x / 2);
    _tab.position.y = (winHeight / 2) - (_tab.getSize().y / 2) - 5;
}

void Core::ListMenuScene::buildTitle()
{
    _title.type     = widget::WidgetType::TEXT;
    _title.text     = getTitleText();
    _title.position = widget::Vec2{.x = _tab.position.x +
            (_tab.getSize().x / 2) - (_title.text.size() / 2),
        .y = _tab.position.y};
}

void Core::ListMenuScene::buildCursors()
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

void Core::ListMenuScene::buildList()
{
    auto yAxis       = _tab.position.y + 2;
    const auto items = getItemNames();

    for (const auto &name: items) {
        _libraries.emplace_back();
        _libraries.back().type     = widget::WidgetType::TEXT;
        _libraries.back().text     = name;
        _libraries.back().position = widget::Vec2{
            .x = (_tab.position.x) + (_tab.getSize().x / 2) - (name.size() / 2),
            .y = yAxis};
        yAxis = yAxis + 2;
    }
}

void Core::ListMenuScene::buildErrorMessage()
{
    _descriptionMessage.type      = widget::WidgetType::TEXT;
    _descriptionMessage.textColor = widget::Color::GREEN;
    _descriptionMessage.position  = widget::Vec2{
         .x = _tab.position.x, .y = _tab.position.y + _tab.getSize().y + 5};
    _descriptionMessage.text = getDescriptionText();
    _errorMessage.type       = widget::WidgetType::TEXT;
    _errorMessage.textColor  = widget::Color::RED;
    _errorMessage.position   = widget::Vec2{
          .x = _tab.position.x, .y = _descriptionMessage.position.y + 2};
    if (_libraries.empty())
        _errorMessage.text = "Error: No library available";
}

void Core::ListMenuScene::buildKeyHelpText()
{
    _keyHelpText.type      = widget::WidgetType::TEXT;
    _keyHelpText.textColor = widget::Color::CYAN;
    _keyHelpText.text =
        "[ENTER | N | RIGHT] Next, [P | LEFT] Prev, [UP | DOWN] Select";
    _keyHelpText.position = widget::Vec2{.x = _tab.position.x +
            (_tab.getSize().x / 2) - (_keyHelpText.text.size() / 2),
        .y = _errorMessage.position.y + 3};
}

void Core::ListMenuScene::buildNavigationButtons()
{
    constexpr std::size_t buttonWidth  = 12;
    constexpr std::size_t buttonHeight = 3;

    _prevButton.type = widget::WidgetType::RECTANGLE;
    _prevButton.setSize(widget::Vec2{.x = buttonWidth, .y = buttonHeight});
    _prevButton.position = widget::Vec2{
        .x = _tab.position.x - buttonWidth - 3, .y = _tab.position.y + 5};
    _prevButton.fillColor              = widget::Color::BLACK;
    _prevButton.decoration.style       = widget::BorderStyle::SOLID;
    _prevButton.decoration.borderColor = widget::Color::WHITE;

    _prevButtonText.type     = widget::WidgetType::TEXT;
    _prevButtonText.text     = "Previous";
    _prevButtonText.position = widget::Vec2{.x = _prevButton.position.x +
            (_prevButton.getSize().x / 2 - _prevButtonText.text.size() / 2),
        .y = _prevButton.position.y + 1};

    _nextButton.type = widget::WidgetType::RECTANGLE;
    _nextButton.setSize(widget::Vec2{.x = buttonWidth, .y = buttonHeight});
    _nextButton.position = widget::Vec2{
        .x = _tab.position.x + _tab.getSize().x + 3, .y = _tab.position.y + 5};
    _nextButton.fillColor              = widget::Color::BLACK;
    _nextButton.decoration.style       = widget::BorderStyle::SOLID;
    _nextButton.decoration.borderColor = widget::Color::WHITE;

    _nextButtonText.type     = widget::WidgetType::TEXT;
    _nextButtonText.text     = "Next";
    _nextButtonText.position = widget::Vec2{.x = _nextButton.position.x +
            (_nextButton.getSize().x / 2 - _nextButtonText.text.size() / 2),
        .y = _nextButton.position.y + 1};
}

void Core::ListMenuScene::buildWidgets()
{
    buildTab();
    buildTitle();
    buildCursors();
    buildList();
    buildErrorMessage();
    buildKeyHelpText();
    buildNavigationButtons();
}

void Core::ListMenuScene::moveCursorDown()
{
    if (_libraries.empty())
        return;

    ++_selectedLib;

    if (_selectedLib == _libraries.end())
        _selectedLib = _libraries.begin();

    _cursorLeft.position.y  = _selectedLib->position.y;
    _cursorRight.position.y = _selectedLib->position.y;
}

void Core::ListMenuScene::moveCursorUp()
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

void Core::ListMenuScene::goToNextScene() const
{
    if (nextScene != nullptr && !_libraries.empty()) {
        onSelect();
        core._currentScene = nextScene;
    }
}

void Core::ListMenuScene::goToPreviousScene() const
{
    if (prevScene != nullptr)
        core._currentScene = prevScene;
}

void Core::ListMenuScene::onSelect() const
{}

void Core::ListMenuScene::handleKeyEvent(const widget::Event &event)
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

void Core::ListMenuScene::handleMouseEvent(const widget::Event &event)
{
    if (event.mouseButton.button != widget::MouseButton::LEFT)
        return;

    const std::size_t eventX = event.mouseButton.x;
    const std::size_t eventY = event.mouseButton.y;

    const std::size_t prevMinX = _prevButton.position.x.getValue();
    const std::size_t prevMaxX = prevMinX + _prevButton.getSize().x.getValue();
    const std::size_t prevMinY = _prevButton.position.y.getValue();
    const std::size_t prevMaxY = prevMinY + _prevButton.getSize().y.getValue();
    if (eventX >= prevMinX && eventX < prevMaxX && eventY >= prevMinY &&
        eventY < prevMaxY) {
        goToPreviousScene();
        return;
    }

    const std::size_t nextMinX = _nextButton.position.x.getValue();
    const std::size_t nextMaxX = nextMinX + _nextButton.getSize().x.getValue();
    const std::size_t nextMinY = _nextButton.position.y.getValue();
    const std::size_t nextMaxY = nextMinY + _nextButton.getSize().y.getValue();
    if (eventX >= nextMinX && eventX < nextMaxX && eventY >= nextMinY &&
        eventY < nextMaxY) {
        goToNextScene();
        return;
    }

    for (auto elem = _libraries.begin(); elem != _libraries.end(); ++elem) {
        const std::size_t minX = _cursorLeft.position.x.getValue();
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
