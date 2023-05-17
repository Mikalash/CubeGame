#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "segment.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    //window.setVerticalSyncEnabled(true);

    class drawer drw(&window);

    const int n_segments = 14;
    class segment sgm[n_segments];
    for (int i = 0; i < n_segments; i++)
        sgm[i].sg_fill(i, 600, i % 7, 0);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (int i = n_segments - 1; i >= 0; i--)
        {
            sgm[i].draw(&drw);
            if (sgm[i].go_ahead(n_segments))
            {
                for (int j = 0; j < n_segments - 1; j++)
                    std::swap(sgm[j], sgm[j + 1]);
            }
        }

        window.display();

        sf::Clock clock;
        while (clock.getElapsedTime().asMilliseconds() < 10);
    }

    return 0;
}
