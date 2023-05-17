#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <SFML/Graphics.hpp>

#include "game_circle.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "CUB(A)Egame");
    //window.setVerticalSyncEnabled(true);

    char fraze_1[1024] = "Use W A S D\n to control\n the square";
    char fraze_2[1024] = "Press any botton\n to start";

    sf::Font font;
    font.loadFromFile("font/myf.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(60);
    text.setColor(sf::Color(0, 200, 200));

    text.setString(fraze_1);
    text.setOrigin(300 - (int)strlen(fraze_1) * 25 / 2, -100);
    window.draw(text);
    text.setString(fraze_2);
    text.setOrigin(300 - (int)strlen(fraze_2) * 25 / 2, -400);
    window.draw(text);
    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                game_circle(&window, 600);
                window.draw(text);
                window.display();
            }
        }
    }

    return 0;
}
