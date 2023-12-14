#pragma once

enum PawnState
{
//PLAYER
    idle,
    jump,
    jumpAttack,
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
    throwAttack
};