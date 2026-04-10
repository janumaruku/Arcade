/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** NameEntryScene
*/

#include "Core.hpp"

namespace arcade {
namespace core {

Core::NameEntryScene::NameEntryScene(Core &core, AScene *next, AScene *prev):
    AScene{core, next, prev}, _tab{widget::Vec2{.x = 0, .y = 0}}
{
    buildWidgets();
}

void Core::NameEntryScene::handleEvent(const widget::Event &event)
{
    switch (event.type) {
    case widget::Event::EventType::CLOSED:
        core.getCurrentDisplay()->closeWindow();
        return;
    case widget::Event::EventType::KEY_PRESSED:
        handleKeyEvent(event);
        return;
    default:
        return;
    }
}

void Core::NameEntryScene::update()
{}

void Core::NameEntryScene::draw()
{
    core.getCurrentDisplay()->draw(_tab);
    core.getCurrentDisplay()->draw(_title);
    core.getCurrentDisplay()->draw(_promptMessage);
    core.getCurrentDisplay()->draw(_nameDisplay);
    core.getCurrentDisplay()->draw(_cursor);
    core.getCurrentDisplay()->draw(_instructionMessage);
}

void Core::NameEntryScene::buildWidgets()
{
    buildTab();
    buildTitle();
    buildPrompt();
    buildNameDisplay();
    buildInstructions();
}

void Core::NameEntryScene::buildTab()
{
    _tab.type = widget::WidgetType::RECTANGLE;
    _tab.setSize(widget::Vec2{.x = 50, .y = 12});
    const auto [winWidth, winHeight] =
        core.getCurrentDisplay()->getWindowSize();
    _tab.position.x = (winWidth / 2) - (_tab.getSize().x / 2);
    _tab.position.y = (winHeight / 2) - (_tab.getSize().y / 2) - 3;
}

void Core::NameEntryScene::buildTitle()
{
    _title.type     = widget::WidgetType::TEXT;
    _title.text     = "Welcome to Arcade";
    _title.position = widget::Vec2{.x = _tab.position.x +
            (_tab.getSize().x / 2) - (_title.text.size() / 2),
        .y = _tab.position.y};
}

void Core::NameEntryScene::buildPrompt()
{
    _promptMessage.type      = widget::WidgetType::TEXT;
    _promptMessage.text      = "Enter your name:";
    _promptMessage.textColor = widget::Color::GREEN;
    _promptMessage.position  = widget::Vec2{.x = _tab.position.x +
            (_tab.getSize().x / 2) - (_promptMessage.text.size() / 2),
         .y = _tab.position.y + 3};
}

void Core::NameEntryScene::buildNameDisplay()
{
    _nameDisplay.type      = widget::WidgetType::TEXT;
    _nameDisplay.text      = "";
    _nameDisplay.textColor = widget::Color::CYAN;
    _nameDisplay.position  = widget::Vec2{.x = _tab.position.x +
            (_tab.getSize().x / 2) - (_nameDisplay.text.size() / 2),
         .y = _tab.position.y + 5};

    _cursor.type      = widget::WidgetType::TEXT;
    _cursor.text      = "_";
    _cursor.textColor = widget::Color::WHITE;
    _cursor.position  = _nameDisplay.position;
}

void Core::NameEntryScene::buildInstructions()
{
    _instructionMessage.type = widget::WidgetType::TEXT;
    _instructionMessage.text =
        "[ENTER] Confirm  [BACKSPACE] Delete  [ESC] Quit";
    _instructionMessage.textColor = widget::Color::YELLOW;
    _instructionMessage.position  = widget::Vec2{.x = _tab.position.x +
            (_tab.getSize().x / 2) - (_instructionMessage.text.size() / 2),
         .y = _tab.position.y + _tab.getSize().y + 2};
}

void Core::NameEntryScene::updateNameDisplay()
{
    _nameDisplay.text = _playerName;
    _nameDisplay.position.x = _tab.position.x + (_tab.getSize().x / 2) -
        (_nameDisplay.text.size() / 2);
    _cursor.position.x = _nameDisplay.position.x + _playerName.size();
}

void Core::NameEntryScene::handleKeyEvent(const widget::Event &event)
{
    switch (event.key.code) {
    case widget::KeyCode::ENTER:
        goToNextScene();
        break;
    case widget::KeyCode::BACKSPACE:
        if (!_playerName.empty()) {
            _playerName.pop_back();
            updateNameDisplay();
        }
        break;
    case widget::KeyCode::ESC:
        core.getCurrentDisplay()->closeWindow();
        break;
    default:
        handleCharInput(event.key.code);
        break;
    }
}

void Core::NameEntryScene::handleCharInput(widget::KeyCode code)
{
    static constexpr std::size_t MAX_NAME_LENGTH = 20;

    if (_playerName.size() >= MAX_NAME_LENGTH)
        return;

    if (code >= widget::KeyCode::KEY_A && code <= widget::KeyCode::KEY_Z) {
        const int character = 'A' +
            (static_cast<int>(code) - static_cast<int>(widget::KeyCode::KEY_A));
        _playerName += character;
        updateNameDisplay();
        return;
    }
    if (code >= widget::KeyCode::KEY_0 && code <= widget::KeyCode::KEY_9) {
        const int character = '0' +
            (static_cast<int>(code) - static_cast<int>(widget::KeyCode::KEY_0));
        _playerName += character;
        updateNameDisplay();
        return;
    }
}

void Core::NameEntryScene::goToNextScene() const
{
    if (!_playerName.empty() && nextScene != nullptr) {
        core._playerName   = _playerName;
        core._currentScene = nextScene;
    }
}

void Core::NameEntryScene::goToPreviousScene() const
{
    if (prevScene != nullptr)
        core._currentScene = prevScene;
}

} // namespace core
} // namespace arcade
