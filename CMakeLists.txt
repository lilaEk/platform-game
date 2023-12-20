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
        "Source Files/stdafx.cpp"
        "Header Files/stdafx.hpp"
        "Source Files/entities/Player.cpp"
        "Header Files/entities/Player.hpp"
        "Source Files/Animation.cpp"
        "Header Files/Animation.hpp"
        "Source Files/entities/Entity.cpp"
        "Header Files/entities/Entity.hpp"
        "Header Files/entities/Pawn.hpp"
        "Header Files/entities/PawnState.hpp"
        "Header Files/Direction.hpp"
        "Source Files/entities/PawnState.cpp"
        "Header Files/entities/PlayerChoice.hpp"
        "Source Files/entities/Enemy.cpp"
        "Header Files/entities/Enemy.hpp"
        "Header Files/entities/EnemyType.hpp"
        "Source Files/entities/enemies/Spider.cpp"
        "Header Files/entities/enemies/Spider.hpp"
        "Source Files/entities/enemies/Bat.cpp"
        "Header Files/entities/enemies/Bat.hpp"
        "Source Files/entities/enemies/Human.cpp"
        "Header Files/entities/enemies/Human.hpp"
        "Source Files/entities/enemies/Hedgehog.cpp"
        "Header Files/entities/enemies/Hedgehog.hpp"
        "Source Files/entities/enemies/Forest_boss.cpp"
        "Header Files/entities/enemies/Forest_boss.hpp")

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