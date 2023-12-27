#pragma once

#include <iostream>
#include <vector>
#include <array>
#include "Game.hpp"

class Cell {
};

const int cellSize = 16;

std::vector<std::array<Cell, Game::height/cellSize>> map;