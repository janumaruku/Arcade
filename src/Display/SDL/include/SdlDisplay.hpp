/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** SDLDisplay
*/

#ifndef ARCADE_SDLDISPLAY_HPP
#define ARCADE_SDLDISPLAY_HPP

#include <chrono>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

#include "DisplayInterface.hpp"

namespace arcade {
namespace display {

class SDLDisplay: public IDisplayModule {
public:
    SDLDisplay();

    ~SDLDisplay() override;

    void closeWindow() noexcept override;

    void openWindow() noexcept override;

    void openWindow(const widget::Vec2 &size) noexcept override;

    [[nodiscard]] bool isOpen() const noexcept override;

    void draw(const widget::AWidget &widget) override;

    void clear(const widget::Color &color) noexcept override;

    void display() noexcept override;

    void playSound(const std::string &soundName) noexcept override;

    void loadResource(const widget::Resource &resources) override;

    [[nodiscard]] widget::Vec2 getWindowSize() const noexcept override;

    bool pollEvent(widget::Event &event) override;

    [[nodiscard]] const std::string &getName() const noexcept override;

private:
    static constexpr int CELL_SIZE         = 16;
    static constexpr int CELL_HEIGHT       = 18;
    static constexpr int DEFAULT_FONT_SIZE = 9;
    static constexpr double TARGET_FPS     = 60.0;

    std::string _libName     = "SDL2";
    std::string _windowTitle = "Arcade - SDL2";
    bool _isOpen{false};
    double _frameRate = 1.0 / TARGET_FPS;
    int _windowWidth;
    int _windowHeight;

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window{
        nullptr, SDL_DestroyWindow};
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> _renderer{
        nullptr, SDL_DestroyRenderer};
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> _font{
        nullptr, TTF_CloseFont};

    std::unordered_map<std::string,
        std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>>
        _textures;
    std::unordered_map<std::string,
        std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>>
        _sounds;

    std::chrono::steady_clock::time_point _startTime;

    const std::unordered_map<widget::Color, SDL_Color> _colorMap = {
        {widget::Color::TRANSPARENT, {0, 0, 0, 0}},
        {widget::Color::BLACK, {0, 0, 0, 255}},
        {widget::Color::RED, {255, 0, 0, 255}},
        {widget::Color::GREEN, {0, 255, 0, 255}},
        {widget::Color::YELLOW, {255, 255, 0, 255}},
        {widget::Color::BLUE, {0, 0, 255, 255}},
        {widget::Color::MAGENTA, {255, 0, 255, 255}},
        {widget::Color::CYAN, {0, 255, 255, 255}},
        {widget::Color::WHITE, {255, 255, 255, 255}},
    };

    const std::unordered_map<SDL_Keycode, widget::KeyCode> _keys = {
        {SDLK_a, widget::KeyCode::KEY_A},
        {SDLK_b, widget::KeyCode::KEY_B},
        {SDLK_c, widget::KeyCode::KEY_C},
        {SDLK_d, widget::KeyCode::KEY_D},
        {SDLK_e, widget::KeyCode::KEY_E},
        {SDLK_f, widget::KeyCode::KEY_F},
        {SDLK_g, widget::KeyCode::KEY_G},
        {SDLK_h, widget::KeyCode::KEY_H},
        {SDLK_i, widget::KeyCode::KEY_I},
        {SDLK_j, widget::KeyCode::KEY_J},
        {SDLK_k, widget::KeyCode::KEY_K},
        {SDLK_l, widget::KeyCode::KEY_L},
        {SDLK_m, widget::KeyCode::KEY_M},
        {SDLK_n, widget::KeyCode::KEY_N},
        {SDLK_o, widget::KeyCode::KEY_O},
        {SDLK_p, widget::KeyCode::KEY_P},
        {SDLK_q, widget::KeyCode::KEY_Q},
        {SDLK_r, widget::KeyCode::KEY_R},
        {SDLK_s, widget::KeyCode::KEY_S},
        {SDLK_t, widget::KeyCode::KEY_T},
        {SDLK_u, widget::KeyCode::KEY_U},
        {SDLK_v, widget::KeyCode::KEY_V},
        {SDLK_w, widget::KeyCode::KEY_W},
        {SDLK_x, widget::KeyCode::KEY_X},
        {SDLK_y, widget::KeyCode::KEY_Y},
        {SDLK_z, widget::KeyCode::KEY_Z},
        {SDLK_0, widget::KeyCode::KEY_0},
        {SDLK_1, widget::KeyCode::KEY_1},
        {SDLK_2, widget::KeyCode::KEY_2},
        {SDLK_3, widget::KeyCode::KEY_3},
        {SDLK_4, widget::KeyCode::KEY_4},
        {SDLK_5, widget::KeyCode::KEY_5},
        {SDLK_6, widget::KeyCode::KEY_6},
        {SDLK_7, widget::KeyCode::KEY_7},
        {SDLK_8, widget::KeyCode::KEY_8},
        {SDLK_9, widget::KeyCode::KEY_9},
        {SDLK_F1, widget::KeyCode::KEY_F1},
        {SDLK_F2, widget::KeyCode::KEY_F2},
        {SDLK_F3, widget::KeyCode::KEY_F3},
        {SDLK_F4, widget::KeyCode::KEY_F4},
        {SDLK_F5, widget::KeyCode::KEY_F5},
        {SDLK_F6, widget::KeyCode::KEY_F6},
        {SDLK_F7, widget::KeyCode::KEY_F7},
        {SDLK_F8, widget::KeyCode::KEY_F8},
        {SDLK_F9, widget::KeyCode::KEY_F9},
        {SDLK_F10, widget::KeyCode::KEY_F10},
        {SDLK_F11, widget::KeyCode::KEY_F11},
        {SDLK_F12, widget::KeyCode::KEY_F12},
        {SDLK_UP, widget::KeyCode::UP},
        {SDLK_DOWN, widget::KeyCode::DOWN},
        {SDLK_RIGHT, widget::KeyCode::RIGHT},
        {SDLK_LEFT, widget::KeyCode::LEFT},
        {SDLK_ESCAPE, widget::KeyCode::ESC},
        {SDLK_RETURN, widget::KeyCode::ENTER},
        {SDLK_BACKSPACE, widget::KeyCode::BACKSPACE},
    };

    void initSDL();

    void openWindowImpl(int width, int height);

    void drawText(const widget::AWidget &widget);

    void drawTile(const widget::AWidget &widget);

    void drawRectangle(const widget::AWidget &widget);

    bool handleKeyEvent(const SDL_Event &sdlEvent, widget::Event &event);

    bool handleMouseEvent(const SDL_Event &sdlEvent, widget::Event &event);

    [[nodiscard]] SDL_Color getColor(widget::Color color) const;

    SDL_Texture *loadTexture(const std::string &path);
};

} // namespace display
} // namespace arcade

#endif // ARCADE_SDLDISPLAY_HPP
