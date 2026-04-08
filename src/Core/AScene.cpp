/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** IScene
*/

#include "Core.hpp"

namespace arcade {
namespace core {
Core::AScene::AScene(Core &core, AScene *next, AScene *prev): _nextScene{next},
    _prevScene{prev}, _core{core}
{}
} // core
} // arcade