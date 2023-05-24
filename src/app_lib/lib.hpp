#pragma once

#include <SFML/Graphics.hpp>

void handleMouseInput(
        sf::Event event,
        int* grid,
        bool& isInputMode,
        bool& isPlaying,
        int GRID_WIDTH,
        int GRID_HEIGHT);

void handleKeyboardInput(sf::Event event);

int wrapValue(int v, int vMax);

void drawGrid(int* grid, int GRID_WIDTH, int GRID_HEIGHT);

void updateGridNext();

void moveGridNextToGrid();

void drawAdditionalInfo();

void initialize();

void processEvents();

void render();
