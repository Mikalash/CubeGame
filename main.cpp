#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "segment.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    window.setVerticalSyncEnabled(true);

    class drawer drw(&window);

    class segment sgm[14];
    for (int i = 0; i < 14; i++)
        sgm[i].sg_fill(i * 200, 600, i % 7, rand() % 8);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::Clock clock;
        while (clock.getElapsedTime().asMilliseconds() < 10);

        for (int i = 13; i >= 0; i--)
        {
            sgm[i].draw(&drw);
            if (sgm[i].go_ahead(14))
            {
                sgm[0].sg_resp(rand() % 8);
                for (int j = 0; j < 13; j++)
                    std::swap(sgm[j], sgm[j + 1]);
            }
        }
        window.display();
    }

    return 0;
}
