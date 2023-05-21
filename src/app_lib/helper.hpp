#pragma once

#include <SFML/Graphics.hpp>

int wrapValue(int v, int vMax);

void handleKeyboardInput(sf::Event event);

void handleMouseInput(
        sf::Event event,
        int* grid,
        bool& isInputMode,
        bool& isPlaying,
        int GRID_WIDTH,
        int GRID_HEIGHT);