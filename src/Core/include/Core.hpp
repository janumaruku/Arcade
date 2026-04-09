#ifndef MYFTP_CORE_HPP
#define MYFTP_CORE_HPP

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

    class GameListScene: public AScene {
    public:
        explicit GameListScene(
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

        virtual void buildTitle();

        void buildCursors();

        virtual void buildList();

        void buildErrorMessage();

        void buildWidgets();

        void moveCursorDown();

        void moveCursorUp();

        void goToNextScene() const;

        void handleKeyEvent(const widget::Event &event);

        void handleMouseEvent(const widget::Event &event);
    };

    class DisplayListScene: public AScene {
    public:
        explicit DisplayListScene(
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

        virtual void buildTitle();

        void buildCursors();

        virtual void buildList();

        void buildErrorMessage();

        void buildWidgets();

        void moveCursorDown();

        void moveCursorUp();

        void goToNextScene() const;

        void goToPreviousScene() const;

        void handleKeyEvent(const widget::Event &event);

        void handleMouseEvent(const widget::Event &event);
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
    display::IDisplayModule *_currentDisplay = nullptr;
    game::IGameModule *_currentGame          = nullptr;
    std::vector<std::unique_ptr<AScene>> _scenes;
    AScene *_currentScene;
    // std::unique_ptr<GameListScene> _gameListScene;

    void buildScenes();

    const GameLibrariesMap &getGameLibraries() const noexcept;

    void loadLibrary(const std::string &libraryPath);

    void loadLibraries();

    display::IDisplayModule *getCurrentDisplay() const noexcept;
};

} // namespace core
} // namespace arcade

#endif // MYFTP_CORE_HPP
