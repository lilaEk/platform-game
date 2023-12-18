#pragma once
#include "iostream"

enum class PawnState {
//PLAYER
    idle,
    jump,
    die,
    roll,
    squat,
    happy,
    push,
    lift,
    hurt,
//ENEMY
    fly,
//BOTH
    pic,
    run,
    directAttack,
    directDoubleAttack,
    throwAttack
};

extern std::ostream& operator<<(std::ostream& os, const PawnState& state);