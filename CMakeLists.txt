cmake_minimum_required(VERSION 3.26)
project(my_game)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0
)

FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(sfml)


add_executable(my_game "Source Files/main.cpp"
        "Header Files/stdafx.hpp"
        "Source Files/gameplay/pawns/Player.cpp"
        "Header Files/gameplay/pawns/Player.hpp"
        "Source Files/gameplay/Animation.cpp"
        "Header Files/gameplay/Animation.hpp"
        "Source Files/gameplay/pawns/Entity.cpp"
        "Header Files/gameplay/pawns/Entity.hpp"
        "Header Files/gameplay/pawns/Pawn.hpp"
        "Header Files/gameplay/pawns/enums/PawnState.hpp"
        "Header Files/gameplay/pawns/enums/Direction.hpp"
        "Source Files/gameplay/pawns/PawnState.cpp"
        "Header Files/gameplay/pawns/enums/PlayerChoice.hpp"
        "Header Files/gameplay/pawns/Enemy.hpp"
        "Header Files/gameplay/pawns/enums/EnemyType.hpp"
        "Source Files/gameplay/pawns/enemies/Spider.cpp"
        "Header Files/gameplay/pawns/enemies/Spider.hpp"
        "Source Files/gameplay/pawns/enemies/Bat.cpp"
        "Header Files/gameplay/pawns/enemies/Bat.hpp"
        "Source Files/gameplay/pawns/enemies/Human.cpp"
        "Header Files/gameplay/pawns/enemies/Human.hpp"
        "Source Files/gameplay/pawns/enemies/Hedgehog.cpp"
        "Header Files/gameplay/pawns/enemies/Hedgehog.hpp"
        "Source Files/gameplay/pawns/enemies/Forest_boss.cpp"
        "Header Files/gameplay/pawns/enemies/Forest_boss.hpp"
        "Source Files/gameplay/map/Cell.cpp"
        "Header Files/gameplay/map/Cell.hpp"
        "Header Files/gameplay/pawns/enums/CellType.hpp"
        "Source Files/gameplay/map/MapManager.cpp"
        "Header Files/gameplay/map/MapManager.hpp"
        "Source Files/gameplay/map/Map.cpp"
        "Header Files/gameplay/map/Map.hpp"
        "Source Files/views/MainMenu.cpp"
        "Header Files/views/MainMenu.hpp"
        "Source Files/Game.cpp"
        "Header Files/Game.hpp"
        "Source Files/views/NextLevel.cpp"
        "Header Files/views/NextLevel.hpp"
        "Source Files/views/GameOver.cpp"
        "Header Files/views/GameOver.hpp"
        "Source Files/views/Gameplay.cpp"
        "Header Files/views/Gameplay.hpp"
        "Header Files/views/ViewType.hpp"
        "Header Files/views/ButtonType.hpp"
        "Source Files/views/Button.cpp"
        "Header Files/views/Button.hpp"
        "Source Files/views/TextInput.cpp"
        "Header Files/views/TextInput.hpp"
)

target_link_libraries(my_game fmt)

target_link_libraries(
        my_game
        fmt
        sfml-graphics
        sfml-window
        sfml-system
)

IF (WIN32)
    add_custom_command(TARGET my_game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:my_game> $<TARGET_FILE_DIR:my_game>
            COMMAND_EXPAND_LISTS
    )
ENDIF ()