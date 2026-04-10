#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include <list>
#include <string>
#include <vector>

#include "DisplayInterface.hpp"
#include "DlLoader.hpp"
#include "GameInterface.hpp"

namespace arcade {
namespace core {

class Core {
    class AScene {
    public:
        explicit AScene(
            Core &core, AScene *next = nullptr, AScene *prev = nullptr);

        virtual ~AScene() = default;

        virtual void handleEvent(const widget::Event &event) = 0;

        virtual void update() = 0;

        virtual void draw() = 0;

        AScene *nextScene = nullptr;
        AScene *prevScene = nullptr;
        Core &core;
    };

    class ListMenuScene: public AScene {
    public:
        explicit ListMenuScene(
            Core &core, AScene *next = nullptr, AScene *prev = nullptr);

        void handleEvent(const widget::Event &event) override;

        void update() override;

        void draw() override;

    protected:
        widget::Rectangle _tab;
        widget::Text _title;
        widget::Text _cursorLeft;
        widget::Text _cursorRight;
        std::list<widget::Text> _libraries;
        widget::Text _descriptionMessage;
        widget::Text _errorMessage;
        std::list<widget::Text>::iterator _selectedLib;

        void buildTab();

        void buildCursors();

        void buildErrorMessage();

        void buildWidgets();

        void moveCursorDown();

        void moveCursorUp();

        void goToNextScene() const;

        void goToPreviousScene() const;

        void handleKeyEvent(const widget::Event &event);

        void handleMouseEvent(const widget::Event &event);

        virtual std::string getTitleText() const = 0;

        virtual std::string getDescriptionText() const = 0;

        virtual std::vector<std::string> getItemNames() const = 0;

        virtual void onSelect() const;

    private:
        void buildTitle();

        void buildList();
    };

    class GameListScene: public ListMenuScene {
    public:
        explicit GameListScene(
            Core &core, AScene *next = nullptr, AScene *prev = nullptr);

    protected:
        std::string getTitleText() const override;

        std::string getDescriptionText() const override;

        std::vector<std::string> getItemNames() const override;

        void onSelect() const override;
    };

    class DisplayListScene: public ListMenuScene {
    public:
        explicit DisplayListScene(
            Core &core, AScene *next = nullptr, AScene *prev = nullptr);

    protected:
        std::string getTitleText() const override;

        std::string getDescriptionText() const override;

        std::vector<std::string> getItemNames() const override;

        void onSelect() const override;
    };

    class NameEntryScene: public AScene {
    public:
        explicit NameEntryScene(
            Core &core, AScene *next = nullptr, AScene *prev = nullptr);

        void handleEvent(const widget::Event &event) override;

        void update() override;

        void draw() override;

    private:
        widget::Rectangle _tab;
        widget::Text _title;
        widget::Text _promptMessage;
        widget::Text _nameDisplay;
        widget::Text _instructionMessage;
        widget::Text _cursor;
        std::string _playerName;

        void buildWidgets();

        void buildTab();

        void buildTitle();

        void buildPrompt();

        void buildNameDisplay();

        void buildInstructions();

        void updateNameDisplay();

        void handleKeyEvent(const widget::Event &event);

        void handleCharInput(widget::KeyCode code);

        void goToNextScene() const;

        void goToPreviousScene() const;
    };

    class GameScene: public AScene {
    public:
        explicit GameScene(
            Core &core, AScene *next = nullptr, AScene *prev = nullptr);

        void handleEvent(const widget::Event &event) override;

        void update() override;

        void draw() override;

    private:
        bool _initialized = false;
        bool _isStarted   = false;

        void initialize();

        void applyDisplaySwap() const;

        void goBackToMenu() const;
    };

public:
    explicit Core(const std::string &libraryPath);

    void run() const;

private:
    using GameLoadersMap    = std::unordered_map<std::string, utils::DLLoader>;
    using DisplayLoadersMap = std::unordered_map<std::string, utils::DLLoader>;
    using GameLibrariesMap =
        std::unordered_map<std::string, std::unique_ptr<game::IGameModule>>;
    using DisplayLibrariesMap = std::unordered_map<std::string,
        std::unique_ptr<display::IDisplayModule>>;
    GameLoadersMap _gameLoaders;
    DisplayLoadersMap _displayLoaders;
    GameLibrariesMap _gameLibraries;
    DisplayLibrariesMap _displayLibraries;
    display::IDisplayModule *_currentDisplay  = nullptr;
    display::IDisplayModule *_selectedDisplay = nullptr;
    game::IGameModule *_currentGame           = nullptr;
    std::vector<std::unique_ptr<AScene>> _scenes;
    AScene *_currentScene{};
    std::string _playerName;

    void buildScenes();

    const GameLibrariesMap &getGameLibraries() const noexcept;

    const DisplayLibrariesMap &getDisplayLibraries() const noexcept;

    void loadLibrary(const std::string &libraryPath);

    void loadLibraries();

    display::IDisplayModule *getCurrentDisplay() const noexcept;
};

} // namespace core
} // namespace arcade

#endif // ARCADE_CORE_HPP
