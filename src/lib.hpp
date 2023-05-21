#pragma once


#include <SFML/Graphics.hpp>

void handleMouseInput(sf::Event event);

void drawGrid();

void updateGridNext();

void moveGridNextToGrid();

void drawAdditionalInfo();

void initialize();

void processEvents();

void render();
