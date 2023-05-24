#include <lib.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <time.h>

const int CELL_SIZE = 30;
const sf::Vector2f CELL_VECTOR(CELL_SIZE, CELL_SIZE);
const int GRID_WIDTH = 30;
const int GRID_HEIGHT = 20;
const int N_CELLS = GRID_WIDTH * GRID_HEIGHT;
int grid[N_CELLS] = {};
int gridNext[N_CELLS];
bool isInputMode = true;

bool isPlaying = true;
int delay = 120;
const int DELAY_INC = 50;

#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define GRAY sf::Color(153, 153, 153)

sf::Font font;
sf::Text textPause;
sf::Text textPlay;
sf::Text textSpeed;
sf::RenderWindow window;

int wrapValue(int v, int vMax)
{
    if (v == -1)
        return vMax - 1;
    if (v == vMax)
        return 0;
    return v;
}

void handleKeyboardInput(sf::Event event)
{
    if (event.key.code == sf::Keyboard::P) {
        if (isInputMode) {
            isInputMode = false;
            std::cout << "Input mode finished. Game started." << std::endl;
        } else {
            isPlaying = !isPlaying;
        }
    } else if (event.key.code == sf::Keyboard::Right)
        delay = std::max(delay - DELAY_INC, 0); // prevent negative value
    else if (event.key.code == sf::Keyboard::Left)
        delay += DELAY_INC;
}

void handleMouseInput(
        sf::Event event,
        int* grid,
        bool& isInputMode,
        bool& isPlaying,
        int GRID_WIDTH,
        int GRID_HEIGHT)
{
    if (isInputMode && event.mouseButton.button == sf::Mouse::Left) {
        int x = event.mouseButton.x / CELL_SIZE;
        int y = event.mouseButton.y / CELL_SIZE;
        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            grid[x + y * GRID_WIDTH] = !grid[x + y * GRID_WIDTH];
            std::cout << "Cell (" << x << ", " << y << ") toggled."
                      << std::endl;
        }
    } else if (!isPlaying && event.mouseButton.button == sf::Mouse::Left) {
        int x = double(event.mouseButton.x) / CELL_SIZE;
        int y = double(event.mouseButton.y) / CELL_SIZE;
        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
            grid[x + y * GRID_WIDTH] = !grid[x + y * GRID_WIDTH];
    }
}

void drawGrid(int* grid, int GRID_WIDTH, int GRID_HEIGHT)
{
    window.clear(WHITE);
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            sf::RectangleShape cell;
            cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
            cell.setSize(CELL_VECTOR);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(GRAY);
            if (grid[x + y * GRID_WIDTH] == 1)
                cell.setFillColor(BLACK);
            else
                cell.setFillColor(WHITE);
            window.draw(cell);
        }
    }
}

void updateGridNext()
{
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if (!isInputMode) {
                if (isPlaying) {
                    int neighborSum = 0;
                    for (int i = -1; i < 2; i++)
                        for (int j = -1; j < 2; j++) {
                            int xi = wrapValue(x + i, GRID_WIDTH);
                            int yj = wrapValue(y + j, GRID_HEIGHT);
                            neighborSum += grid[xi + yj * GRID_WIDTH];
                        }

                    int current = x + y * GRID_WIDTH;
                    neighborSum -= grid[current];
                    gridNext[current] = grid[current];
                    if (grid[current] == 1
                        && (neighborSum < 2 || neighborSum > 3))
                        gridNext[current] = 0;
                    else if (neighborSum == 3)
                        gridNext[current] = 1;
                }
            }
        }
    }
}

void moveGridNextToGrid()
{
    if (!isInputMode) {
        if (isPlaying) {
            for (int i = 0; i < N_CELLS; i++)
                grid[i] = gridNext[i];
        }
    }
}

void drawAdditionalInfo()
{
    window.draw(textSpeed);
    if (isPlaying)
        window.draw(textPause);
    else if (!isPlaying) {
        window.draw(textPlay);
    }
}

void initialize()
{
    srand(time(NULL));
    for (int i = 0; i < N_CELLS; i++)
        grid[i] = (double(rand()) / RAND_MAX < 0.1) ? 1 : 0;

    font.loadFromFile("../fonts/arial.ttf");

    textPause.setString("Press 'p' to pause.");
    textPause.setFont(font);
    textPause.setCharacterSize(20);
    textPause.setPosition(10, CELL_SIZE * GRID_HEIGHT + 5);
    textPause.setFillColor(BLACK);

    textPlay.setString("Game is paused. Press 'p' to play.");
    textPlay.setFont(font);
    textPlay.setCharacterSize(20);
    textPlay.setPosition(10, CELL_SIZE * GRID_HEIGHT + 5);
    textPlay.setFillColor(BLACK);

    textSpeed.setString("Use left/right arrow keys to change speed.");
    textSpeed.setFont(font);
    textSpeed.setCharacterSize(20);
    textSpeed.setPosition(500, CELL_SIZE * GRID_HEIGHT + 5);
    textSpeed.setFillColor(BLACK);

    window.create(
            sf::VideoMode(CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT + 50),
            "Game of Life");
}

void processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            handleKeyboardInput(event);
            break;
        case sf::Event::MouseButtonPressed:
            handleMouseInput(
                    event,
                    grid,
                    isInputMode,
                    isPlaying,
                    GRID_WIDTH,
                    GRID_HEIGHT);
            drawGrid(
                    grid,
                    GRID_WIDTH,
                    GRID_HEIGHT); // Обновление отображения
                                  // после изменения
                                  // состояния клеток
            window.display(); // Обновление экрана
            break;
        default:
            break;
        }
    }
}

void render()
{
    drawGrid(grid, GRID_WIDTH, GRID_HEIGHT);
    updateGridNext();
    moveGridNextToGrid();
    drawAdditionalInfo();
    window.display();
    sf::sleep(sf::milliseconds(delay));
}