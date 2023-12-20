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
        "Source Files/Game.cpp"
        "Header Files/Game.hpp"
        "Header Files/stdafx.hpp"
        "Source Files/pawns/Player.cpp"
        "Header Files/pawns/Player.hpp"
        "Source Files/Animation.cpp"
        "Header Files/Animation.hpp"
        "Source Files/pawns/Entity.cpp"
        "Header Files/pawns/Entity.hpp"
        "Header Files/pawns/Pawn.hpp"
        "Header Files/pawns/enums/PawnState.hpp"
        "Header Files/pawns/enums/Direction.hpp"
        "Source Files/pawns/PawnState.cpp"
        "Header Files/pawns/enums/PlayerChoice.hpp"
        "Source Files/pawns/Enemy.cpp"
        "Header Files/pawns/Enemy.hpp"
        "Header Files/pawns/enums/EnemyType.hpp"
        "Source Files/pawns/enemies/Spider.cpp"
        "Header Files/pawns/enemies/Spider.hpp"
        "Source Files/pawns/enemies/Bat.cpp"
        "Header Files/pawns/enemies/Bat.hpp"
        "Source Files/pawns/enemies/Human.cpp"
        "Header Files/pawns/enemies/Human.hpp"
        "Source Files/pawns/enemies/Hedgehog.cpp"
        "Header Files/pawns/enemies/Hedgehog.hpp"
        "Source Files/pawns/enemies/Forest_boss.cpp"
        "Header Files/pawns/enemies/Forest_boss.hpp")

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