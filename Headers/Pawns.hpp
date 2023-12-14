#pragma once

#include "Entity.hpp"
#include "Animation.hpp"
#include "PawnState.hpp"


class Pawns : public Entity, public Animation {
    PawnState pawnState;
};