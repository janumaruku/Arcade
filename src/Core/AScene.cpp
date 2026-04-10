/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** IScene
*/

#include "Core.hpp"

namespace arcade {
namespace core {
Core::AScene::AScene(Core &core, AScene *next, AScene *prev): nextScene{next},
    prevScene{prev}, core{core}
{}
} // core
} // arcade