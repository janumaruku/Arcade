/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** SDLDisplay
*/

#include "SdlDisplay.hpp"

#include <SDL2/SDL_image.h>
#include <thread>

namespace arcade {
namespace display {

SDLDisplay::SDLDisplay() = default;

SDLDisplay::~SDLDisplay()
{
    closeWindow();
}

void SDLDisplay::closeWindow() noexcept
{
    if (!_isOpen)
        return;

    _textures.clear();
    _sounds.clear();
    _font.reset();
    _renderer.reset();
    _window.reset();

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    _isOpen = false;
}

void SDLDisplay::openWindow() noexcept
{
    if (_isOpen)
        return;

    initSDL();
    openWindowImpl(0, 0);
    _isOpen = true;
}

void SDLDisplay::openWindow(const widget::Vec2 &size) noexcept
{
    if (_isOpen)
        return;

    initSDL();
    const int width  = size.x.getValue() * CELL_SIZE;
    const int height = size.y.getValue() * CELL_SIZE;
    openWindowImpl(width > 0 ? width : DEFAULT_WIDTH,
        height > 0 ? height : DEFAULT_HEIGHT);
    _isOpen = true;
}

bool SDLDisplay::isOpen() const noexcept
{
    return _isOpen;
}

void SDLDisplay::draw(const widget::AWidget &widget)
{
    if (!_isOpen)
        return;

    drawText(widget);
    drawTile(widget);
    drawRectangle(widget);
}

void SDLDisplay::clear(const widget::Color &color) noexcept
{
    if (!_isOpen)
        return;

    const SDL_Color sdlColor = getColor(color);
    SDL_SetRenderDrawColor(
        _renderer.get(), sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
    SDL_RenderClear(_renderer.get());
}

void SDLDisplay::display() noexcept
{
    if (!_isOpen)
        return;

    SDL_RenderPresent(_renderer.get());

    const std::chrono::steady_clock::time_point timeNow =
        std::chrono::steady_clock::now();
    const std::chrono::duration<double> elapsedTime =
        std::chrono::duration_cast<std::chrono::duration<double>>(
            timeNow - _startTime);

    if (elapsedTime.count() < _frameRate)
        std::this_thread::sleep_for(
            std::chrono::duration<double>(_frameRate - elapsedTime.count()));

    _startTime = std::chrono::steady_clock::now();
}

void SDLDisplay::playSound(const std::string &soundName) noexcept
{
    if (!_isOpen)
        return;

    const auto itt = _sounds.find(soundName);
    if (itt != _sounds.end()) {
        Mix_PlayChannel(-1, itt->second.get(), 0);
    }
}

void SDLDisplay::loadResource(const widget::Resource &resources)
{
    if (!_isOpen)
        return;

    for (const auto &[name, path]: resources.textures) {
        SDL_Texture *texture = loadTexture(path);
        if (texture != nullptr) {
            _textures.emplace(name,
                std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>(
                    texture, SDL_DestroyTexture));
        }
    }

    for (const auto &[name, path]: resources.sounds) {
        Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
        if (chunk != nullptr) {
            _sounds.emplace(name,
                std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>(
                    chunk, Mix_FreeChunk));
        }
    }
}

widget::Vec2 SDLDisplay::getWindowSize() const noexcept
{
    return {.x = _windowWidth / CELL_SIZE, .y = _windowHeight / CELL_SIZE};
}

bool SDLDisplay::pollEvent(widget::Event &event)
{
    if (!_isOpen)
        return false;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_QUIT) {
            event.type = widget::Event::EventType::CLOSED;
            return true;
        }
        if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP) {
            if (handleKeyEvent(sdlEvent, event))
                return true;
        }
        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN ||
            sdlEvent.type == SDL_MOUSEBUTTONUP) {
            if (handleMouseEvent(sdlEvent, event))
                return true;
        }
    }
    return false;
}

const std::string &SDLDisplay::getName() const noexcept
{
    return _libName;
}

void SDLDisplay::initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error(
            std::string("SDL_Init failed: ") + SDL_GetError());
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Quit();
        throw std::runtime_error(
            std::string("IMG_Init failed: ") + IMG_GetError());
    }

    if (TTF_Init() < 0) {
        IMG_Quit();
        SDL_Quit();
        throw std::runtime_error(
            std::string("TTF_Init failed: ") + TTF_GetError());
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        throw std::runtime_error(
            std::string("Mix_OpenAudio failed: ") + Mix_GetError());
    }
}

void SDLDisplay::openWindowImpl(int width, int height)
{
    if (width == 0 && height == 0) {
        SDL_DisplayMode mode;
        if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
            _windowWidth  = mode.w;
            _windowHeight = mode.h;
        }
    } else {
        _windowWidth  = width;
        _windowHeight = height;
    }

    _window.reset(SDL_CreateWindow(_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN));

    if (_window == nullptr) {
        throw std::runtime_error(
            std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    }
    SDL_GetWindowSize(_window.get(), &_windowWidth, &_windowHeight);

    _renderer.reset(SDL_CreateRenderer(_window.get(), -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    if (_renderer == nullptr) {
        _window.reset();
        throw std::runtime_error(
            std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
    }

    _font.reset(TTF_OpenFont("assets/font.ttf", DEFAULT_FONT_SIZE));
    if (_font == nullptr) {
        _renderer.reset();
        _window.reset();
        throw std::runtime_error(
            std::string("TTF_OpenFont failed: ") + TTF_GetError());
    }

    _startTime = std::chrono::steady_clock::now();
}

void SDLDisplay::drawText(const widget::AWidget &widget)
{
    if (widget.type != widget::WidgetType::TEXT)
        return;

    const auto &text = dynamic_cast<const widget::Text &>(widget);
    if (text.text.empty())
        return;

    const SDL_Color textColor = getColor(text.textColor);
    const SDL_Color bgColor   = getColor(text.backgroundColor);

    SDL_Surface *surface = nullptr;
    if (text.backgroundColor == widget::Color::TRANSPARENT) {
        surface =
            TTF_RenderText_Blended(_font.get(), text.text.c_str(), textColor);
    } else {
        surface = TTF_RenderText_Shaded(
            _font.get(), text.text.c_str(), textColor, bgColor);
    }

    if (surface == nullptr)
        return;

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(_renderer.get(), surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr)
        return;

    const int xPos = text.position.x.getValue() * CELL_SIZE;
    const int yPos = text.position.y.getValue() * CELL_SIZE;

    int textWidth  = 0;
    int textHeight = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

    const SDL_Rect destRect = {xPos, yPos, textWidth, textHeight};
    SDL_RenderCopy(_renderer.get(), texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
}

void SDLDisplay::drawTile(const widget::AWidget &widget)
{
    if (widget.type != widget::WidgetType::TILE)
        return;

    const auto &tile = dynamic_cast<const widget::Tile &>(widget);

    const int xPos = tile.position.x.getValue() * CELL_SIZE;
    const int yPos = tile.position.y.getValue() * CELL_SIZE;

    // Try to draw texture if available
    if (!tile.textureName.empty()) {
        const auto itt = _textures.find(tile.textureName);
        if (itt != _textures.end()) {
            const SDL_Rect srcRect  = {tile.rect.x, tile.rect.y,
                 static_cast<int>(tile.rect.width),
                 static_cast<int>(tile.rect.height)};
            const SDL_Rect destRect = {xPos, yPos, CELL_SIZE, CELL_SIZE};
            SDL_RenderCopy(
                _renderer.get(), itt->second.get(), &srcRect, &destRect);
            return;
        }
    }

    // Draw background color
    if (tile.backgroundColor != widget::Color::TRANSPARENT) {
        const SDL_Color bgColor = getColor(tile.backgroundColor);
        SDL_SetRenderDrawColor(
            _renderer.get(), bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        const SDL_Rect bgRect = {xPos, yPos, CELL_SIZE, CELL_SIZE};
        SDL_RenderFillRect(_renderer.get(), &bgRect);
    }

    // Draw symbol as text fallback
    if (!tile.symbol.empty()) {
        const SDL_Color color = getColor(tile.color);
        SDL_Surface *surface =
            TTF_RenderText_Blended(_font.get(), tile.symbol.c_str(), color);

        if (surface != nullptr) {
            SDL_Texture *texture =
                SDL_CreateTextureFromSurface(_renderer.get(), surface);
            SDL_FreeSurface(surface);

            if (texture != nullptr) {
                int textWidth  = 0;
                int textHeight = 0;
                SDL_QueryTexture(
                    texture, nullptr, nullptr, &textWidth, &textHeight);

                const SDL_Rect destRect = {xPos + (CELL_SIZE - textWidth) / 2,
                    yPos + (CELL_SIZE - textHeight) / 2, textWidth, textHeight};
                SDL_RenderCopy(_renderer.get(), texture, nullptr, &destRect);
                SDL_DestroyTexture(texture);
            }
        }
    }
}

void SDLDisplay::drawRectangle(const widget::AWidget &widget)
{
    if (widget.type != widget::WidgetType::RECTANGLE)
        return;

    const auto &rectangle = dynamic_cast<const widget::Rectangle &>(widget);

    const int xPos   = rectangle.position.x.getValue() * CELL_SIZE;
    const int yPos   = rectangle.position.y.getValue() * CELL_SIZE;
    const int width  = rectangle.getSize().x.getValue() * CELL_SIZE;
    const int height = rectangle.getSize().y.getValue() * CELL_SIZE;

    // Try to draw texture if available
    if (!rectangle.textureName.empty()) {
        const auto itt = _textures.find(rectangle.textureName);
        if (itt != _textures.end()) {
            const SDL_Rect destRect = {xPos, yPos, width, height};
            SDL_RenderCopy(
                _renderer.get(), itt->second.get(), nullptr, &destRect);
            return;
        }
    }

    // Draw fill color
    if (rectangle.fillColor != widget::Color::TRANSPARENT) {
        const SDL_Color fillColor = getColor(rectangle.fillColor);
        SDL_SetRenderDrawColor(_renderer.get(), fillColor.r, fillColor.g,
            fillColor.b, fillColor.a);
        const SDL_Rect fillRect = {xPos, yPos, width, height};
        SDL_RenderFillRect(_renderer.get(), &fillRect);
    }

    // Draw border if style is SOLID
    if (rectangle.decoration.style == widget::BorderStyle::SOLID) {
        const SDL_Color borderColor =
            getColor(rectangle.decoration.borderColor);
        SDL_SetRenderDrawColor(_renderer.get(), borderColor.r, borderColor.g,
            borderColor.b, borderColor.a);
        const SDL_Rect borderRect = {xPos, yPos, width, height};
        SDL_RenderDrawRect(_renderer.get(), &borderRect);
    }
}

bool SDLDisplay::handleKeyEvent(const SDL_Event &sdlEvent, widget::Event &event)
{
    const auto itt = _keys.find(sdlEvent.key.keysym.sym);
    if (itt == _keys.end())
        return false;

    event.type      = (sdlEvent.type == SDL_KEYDOWN)
             ? widget::Event::EventType::KEY_PRESSED
             : widget::Event::EventType::KEY_RELEASED;
    event.key.code  = itt->second;
    event.key.alt   = (sdlEvent.key.keysym.mod & KMOD_ALT) != 0;
    event.key.ctrl  = (sdlEvent.key.keysym.mod & KMOD_CTRL) != 0;
    event.key.shift = (sdlEvent.key.keysym.mod & KMOD_SHIFT) != 0;
    return true;
}

bool SDLDisplay::handleMouseEvent(
    const SDL_Event &sdlEvent, widget::Event &event)
{
    event.type = (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
        ? widget::Event::EventType::MOUSE_BUTTON_PRESSED
        : widget::Event::EventType::MOUSE_BUTTON_RELEASED;

    switch (sdlEvent.button.button) {
    case SDL_BUTTON_LEFT:
        event.mouseButton.button = widget::MouseButton::LEFT;
        break;
    case SDL_BUTTON_RIGHT:
        event.mouseButton.button = widget::MouseButton::RIGHT;
        break;
    default:
        event.mouseButton.button = widget::MouseButton::NONE;
        return false;
    }

    event.mouseButton.x = sdlEvent.button.x / CELL_SIZE;
    event.mouseButton.y = sdlEvent.button.y / CELL_SIZE;
    return true;
}

SDL_Color SDLDisplay::getColor(widget::Color color) const
{
    const auto itt = _colorMap.find(color);
    if (itt != _colorMap.end())
        return itt->second;
    return _colorMap.at(widget::Color::WHITE);
}

SDL_Texture *SDLDisplay::loadTexture(const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
        return nullptr;

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(_renderer.get(), surface);
    SDL_FreeSurface(surface);
    return texture;
}

} // namespace display
} // namespace arcade

extern "C" arcade::display::IDisplayModule *entryPointDisplay()
{
    return new arcade::display::SDLDisplay();
}
