#pragma once

#include <SFML/Graphics.hpp>

void drawGrid(int* grid, int GRID_WIDTH, int GRID_HEIGHT);

void updateGridNext();

void moveGridNextToGrid();

void drawAdditionalInfo();

void initialize();

void processEvents();

void render();
