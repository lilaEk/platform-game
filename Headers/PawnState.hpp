#pragma once

enum PawnState
{
//PLAYER
    idle,
    jump, //w lewo i w prawo
    jumpAttack, //w lewo i w prawo
    die,
    roll, //w lewo i w prawo
    squat, //w lewo i w prawo
    happy,
    push, //w lewo i w prawo
    lift, //w lewo i w prawo
    hurt, //w lewo i w prawo
//ENEMY
    fly, //w lewo i w prawo
//BOTH
    pic,
    run, //w lewo i w prawo
    directAttack, //w lewo i w prawo
    throwAttack //w lewo i w prawo
};