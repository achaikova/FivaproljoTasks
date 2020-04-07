#pragma once

namespace Utilities {

    enum class Direction {
        RIGHT,
        LEFT,
        UP,
        DOWN,
        UNKNOWN
    };

    enum class Color {
        NONE,
        GREEN,
        YELLOW
    };

    enum class GameState {
        INITIALIZING,
        MENU_NUM_OF_PLAYERS,
        MENU_MODE,
        LEVEL_ON,
        EXIT
    };

    enum class GameMode {
        SINGLE_PLAYER,
        TWO_PLAYERS,
    };

} // end namespace Utilities

namespace KeyPresserUtility {

    enum class ManipulatorType {
        PLAYER,
        MENU
    };

} // end namespace KeyPresserUtilitie

#define unused(p) (void)p
