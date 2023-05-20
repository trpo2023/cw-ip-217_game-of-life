#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "../src/lib.hpp"

int main()
{
    initialize();
    sf::RenderWindow window1;
    window1.create(sf::VideoMode(200,1), "Exit");

 while (window1.isOpen())
    {
        processEvents();
        render();

        sf::Event event;
        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window1.close();
        }
    }

    return 0;
}
