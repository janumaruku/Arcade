/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** IScene
*/

#ifndef ARCADE_ASCENE_HPP
#define ARCADE_ASCENE_HPP

#include "DisplayInterface.hpp"
#include "Widget.hpp"

namespace arcade {
namespace core {

class AScene {
public:
    virtual ~AScene() = default;

    virtual void handleEvent(const widget::Event &event) = 0;

    virtual void update() = 0;

    virtual void draw(display::IDisplayModule &display) = 0;

protected:
    AScene *nextScene = nullptr;
    AScene *prevScene = nullptr;
};

} // core
} // arcade

#endif //ARCADE_ASCENE_HPP
