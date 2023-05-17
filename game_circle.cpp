#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <SFML/Graphics.hpp>

#include "drawer.cpp"
#include "segment.cpp"
#include "player.cpp"

void show_score(sf::RenderWindow *window, float score);

void game_circle(sf::RenderWindow *window, int scr_len)
{
    float score = 0.25;

    class drawer drw(window);

    const int n_segments = 14;
    class segment sgm[n_segments];
    for (int i = 0; i < n_segments; i++)
        sgm[i].sg_fill(i, scr_len, i % 7, 0);

    class player plr(scr_len);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
                return;
            }
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

        window->clear();

        for (int i = n_segments - 1; i >= 0; i--)
        {
            sgm[i].draw(&drw);
            if (sgm[i].go_ahead())
            {
                if (plr.is_crash(sgm[i].get_mask_index()))
                {
                    sf::Clock clock;
                    while (clock.getElapsedTime().asSeconds() < 3);
                    return;
                }

                sgm[i].respawn(n_segments);
                for (int j = 0; j < n_segments - 1; j++)
                    std::swap(sgm[j], sgm[j + 1]);
            }
        }

        plr.draw(&drw);
        plr.calc_bonus(score);
        show_score(window, score);

        window->display();

        sf::Clock clock;
        while (clock.getElapsedTime().asMilliseconds() < (int) (2.5 / score));
        score += 0.0002 * score * score;

        //std::cout << score << "\n";
    }

}

void show_score(sf::RenderWindow *window, float score)
{
    char string_score[1024];
    itoa((int)(score * 1000 - 250), string_score, 10);
    std::cout << string_score << "\n";

    sf::Font font;
    font.loadFromFile("font/myf.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(60);
    text.setColor(sf::Color(0, 200, 200));

    text.setString(string_score);
    text.setOrigin(-300 + (int)strlen(string_score) * 25 / 2, -20);
    window->draw(text);
}
