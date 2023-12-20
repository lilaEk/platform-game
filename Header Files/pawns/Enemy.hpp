#pragma once

#include "Pawn.hpp"
#include "../Animation.hpp"

class Enemy : public Pawn {

private:
    std::vector<Enemy *> allEnemies;

};