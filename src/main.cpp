#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "../src/lib.hpp"
#include "test.hpp"

const int CELL_SIZE = 30;
const int GRID_WIDTH = 30;
const int GRID_HEIGHT = 20;

int main(int argc, char** argv)
{
    // Проверяем наличие аргумента командной строки "nographic" для запуска только тестов без открытия графического окна
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "nographic")
        {
            // Запускаем тесты без открытия графического окна
            return mainTest(argc, argv);
        }
    }

    initialize();

    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * GRID_WIDTH, CELL_SIZE * GRID_HEIGHT + 50), "Game of Life");

    while (window.isOpen())
    {
        processEvents();  // Обработка событий
        render();  // Отрисовка

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    // Запуск тестов после окончания работы программы
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
