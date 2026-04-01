/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** NcursesDisplay
*/

#include "NcursesDisplay.hpp"

namespace arcade {
namespace display {
NcursesDisplay::~NcursesDisplay() = default;

void NcursesDisplay::closeWindow() noexcept
{}

void NcursesDisplay::openWindow() noexcept
{}

void NcursesDisplay::openWindow(const widget::Vec2 &/*size*/) noexcept
{}

bool NcursesDisplay::isOpen() const noexcept
{
    return false;
}

void NcursesDisplay::draw(const widget::AWidget &/*widget*/)
{}

void NcursesDisplay::clear(const widget::Color &/*color*/) noexcept
{}

void NcursesDisplay::display() noexcept
{}

void NcursesDisplay::playSound(const std::string &/*soundName*/) noexcept
{}

void NcursesDisplay::loadResource(const widget::Resource &/*resources*/)
{}

widget::Vec2 NcursesDisplay::getWindowSize() const noexcept
{
    return {.x=0, .y=0};
}

bool NcursesDisplay::pollEvent(widget::Event &/*event*/)
{
    return false;
}

const std::string & NcursesDisplay::getName() const noexcept
{
    return "Ncurses";
}
} // namespace display
} // namespace arcade

extern "C" arcade::display::IDisplayModule *entryPointDisplay()
{
    return new arcade::display::NcursesDisplay();
}
