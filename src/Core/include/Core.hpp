#ifndef MYFTP_CORE_HPP
#define MYFTP_CORE_HPP

#include <list>
#include <string>

#include "DisplayInterface.hpp"
#include "DlLoader.hpp"
#include "GameInterface.hpp"

namespace arcade {
namespace core {

class Core {
    class AScene {
    public:
        explicit AScene(Core &core, AScene *next = nullptr,
            AScene *prev                         = nullptr);

        virtual ~AScene() = default;

        virtual void handleEvent(const widget::Event &event) = 0;

        virtual void update() = 0;

        virtual void draw() = 0;

    protected:
        AScene *_nextScene = nullptr;
        AScene *_prevScene = nullptr;
        Core &_core;
    };

    class GameListScene: public AScene {
    public:
        explicit GameListScene(Core &core, AScene *next = nullptr,
            AScene *prev                                = nullptr);

        void handleEvent(const widget::Event &event) override;

        void update() override;

        void draw() override;

    private:
        widget::Rectangle _tab;
        widget::Text _gamesTitle;
        widget::Text _cursorLeft;
        widget::Text _cursorRight;
        std::list<widget::Text> _gameLibraries;
        widget::Text _errorMessage;
        std::list<widget::Text>::iterator _selectedGame;

        void buildTab();

        void buildTitle();

        void buildCursors();

        void buildList();

        void buildErrorMessage();

        void buildWidgets();

        void moveCursorDown();

        void moveCursorUp();

        void handleKeyEvent(const widget::Event &event);

        void handleMouseEvent(widget::Event event);
    };

public:
    explicit Core(const std::string &libraryPath);

private:
    using GameLoadersMap    = std::unordered_map<std::string, utils::DLLoader>;
    using DisplayLoadersMap = std::unordered_map<std::string, utils::DLLoader>;
    using GameLibrariesMap  = std::unordered_map<std::string, std::unique_ptr<
        game::IGameModule>>;
    using DisplayLibrariesMap = std::unordered_map<std::string, std::unique_ptr<
        display::IDisplayModule>>;
    GameLoadersMap _gameLoaders;
    DisplayLoadersMap _displayLoaders;
    GameLibrariesMap _gameLibraries;
    DisplayLibrariesMap _displayLibraries;
    display::IDisplayModule *_currentDisplay;
    std::unique_ptr<GameListScene> _gameListScene;

    const GameLibrariesMap &getGameLibraries() const noexcept;

    void loadLibrary(const std::string &libraryPath);

    void loadLibraries();

    display::IDisplayModule *getCurrentDisplay() const noexcept;
};

} // core
} // arcade

#endif //MYFTP_CORE_HPP
