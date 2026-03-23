# Arcade
Arcade is a **gaming platform**: a program that lets the user choose a game to play and keeps a register of player scores. And the purpose of this project is to create a gaming platform capable of running multiple games in different graphic environments. To achieve this goal, the project will be split into three main modules:

- The **Game Module**: which deals with the game logic. It manages tasks like player movements, player scores, game states, background music, reward sounds, ... It gets inputs from the **Core Module** to manage the game state. The **Game Module** provides an interface to the **Core Module**, to access the game state on each frame.

- The **Display Module**: which deals with graphics (window, shape drawing) and events (mouse events, keyboard events, ...). It provides an interface to the **Core module**, and this interface provides features like create a window, open the window, draw and display figures on the window, get events on that window, and many other features.

- The **Core Module**: It's the orchestrator of the whole program. Everything is handled there, including game libraries and graphic libraries. The Core starts with a graphic library, chosen at the start. It loads the libraries, located at a given path. It manages multiple views: main menu view, in game menu view, game view, and maybe other (settings, ...). It builds the game view using the game interface. It gets events from the graphic interface and sends them back to the game instance. It gets new game states per frame and displays them using the graphic interface.

## Project description
To be able to deal with the game platform at run-time, the graphic libraries and the games must be implemented as **dynamic libraries**, loaded at runtime.

> It is **STRICTLY FORBIDDEN** to refer to a graphic library in the main program. Only dynamic graphics libraries can do so.

Dynamic libraries must be used at runtime, which means the `libdl` interface functions, `dlopen`, `dlsym`, `dlclose` and `dlerror`, will be used to handle the libraries.

> `libdl` is a `C` library. An encapsulation of the library (at least the four used functions) should be provided. The compilation flag `-fno-gnu-uni` to the compilation stage to ensure `dlclose` unloads the libraries properly.

> Pay attention to the dependency graph. There should not be any direct dependency between the three modules.

### Graphics libraries
The `nCurses` (`arcade_ncurses.so`) and the `SDL2` (`arcade_sdl2.so`) libraries should be implemented and at least one more from this list:
- `NDK++` (`arcade_ndk++.so`)
- `aa-lib` (`arcade_aalib.so`)
- `libcaca` (`arcade_libcaca.so`)
- `Allegro5` (`arcade_allegro5.so`)
- `Xlib` (`arcade_xlib.so`)
- `GTK+` (`arcade_gtk+.so`)
- `SFML` (`arcade_sfml.so`)
- `Irrlicht` (`arcade_irrlicht.so`)
- `OpenGL` (`arcade_opengl.so`)
- `Vulkan` (`arcade_vulkan.so`)
- `Qt5` (`arcade_qt5.so`)

### Game libraries
At least two games from the following list must be implemented:
- Snake (`arcade_snake.so`)
- Minesweeper (`arcade_minesweeper.so`)
- Nibbler (`arcade_nibbler.so`)
- Pacman (`arcade_pacman.so`)
- Qix (`arcade_qix.so`)
- Centipede (`arcade_centipede.so`)
- Solarfox (`arcade_solarfox.so`)

# Build
The project can be built using either `make` (`Makefile`) or `cmake` (`CMakeList.txt`)

## Makefile
The `Makefile` will have the following rules (in addition to `all`, `re`, `clean` and `fclean`):
- `core`: that only builds the **Core module**.
- `games`: that only builds the **Game module**, the game libraries.
- `graphicals`: that only builds the **Graphic module**, the graphics libraries.

## CMake
The project must have a `CMakelists.txt` file located at the root of the repository. The CMake configuration must build at least three graphics dynamic libraries and at least two game dynamic libraries at the root of the repository.

```shell
$> cmake -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
[...]

$> cmake --build build
[...]

$> ls ./arcade ./lib/
./arcade

./lib/:
arcade_ncurses.so
arcade_pacman.so
arcade_sdl2.so
arcade_sfml.so
arcade_nibbler.so
...
```

# Usage
The program must take, at startup, the graphical library to initially start with.

```shell
$> ./arcade ./lib/arcade_ncurses.so
```

# Contributor
This project was carried out by a group of three consisting of:
- [Albane HERAUD](albane.heraud@epitech.eu)
- [G. Jean-Marc KOTTIN](jean-marc.kottin@epitech.eu)
- [Nicky TRUONG](nicky.truong@epitech.eu)

The project interfaces were shared with another group consisting of:

