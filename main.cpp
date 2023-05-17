#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "drawer.cpp"
#include "segment.cpp"
#include "player.cpp"

int main()
{
    float score = 0.25;
    sf::RenderWindow window(sf::VideoMode(600, 600), "CUB(A)Egame");
    //window.setVerticalSyncEnabled(true);

    class drawer drw(&window);

    const int n_segments = 14;
    class segment sgm[n_segments];
    for (int i = 0; i < n_segments; i++)
        sgm[i].sg_fill(i, 600, i % 7, 0);

    class player plr(600);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case (sf::Keyboard::W):
                        plr.moved('w');
                        break;
                    case (sf::Keyboard::D):
                        plr.moved('d');
                        break;
                    case (sf::Keyboard::S):
                        plr.moved('s');
                        break;
                    case (sf::Keyboard::A):
                        plr.moved('a');
                        break;
                }
            }
        }

        window.clear();

        for (int i = n_segments - 1; i >= 0; i--)
        {
            sgm[i].draw(&drw);
            if (sgm[i].go_ahead())
            {
                if (plr.is_crash(sgm[i].get_mask_index()))
                {
                    sf::Clock clock;
                    while (clock.getElapsedTime().asSeconds() < 10);
                }

                sgm[i].respawn(n_segments);
                for (int j = 0; j < n_segments - 1; j++)
                    std::swap(sgm[j], sgm[j + 1]);
            }
        }

        plr.draw(&drw);
        plr.calc_bonus(score);

        window.display();

        sf::Clock clock;
        while (clock.getElapsedTime().asMilliseconds() < (int) (2.5 / score));
        score += 0.0002 * score * score;
        std::cout << score << "\n";
    }

    return 0;
}
