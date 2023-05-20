#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "../src/lib.hpp"

int main()
{
    initialize();

    while (window.isOpen())
    {
        processEvents();
        render();
    }

    return 0;
}
