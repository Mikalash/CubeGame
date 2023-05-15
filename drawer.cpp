#include <SFML/Graphics.hpp>

class tetrahed
{
    int x[4];
    int y[4];
};

void fill_trh(struct tetrahed* trh, int* in_x, int* in_y);

void sort_trh(struct tetrahed* trh);

class drawer
{
    private:
        sf::RenderWindow *window;
    public:
        drawer(sf::RenderWindow *in_window)
        {
            window = in_window;
        }

        void draw_trh(struct tetrahed* trh, int color, int bright)
        {
            sort_trh(trh);

            sf::VertexArray triangle(sf::Triangles, 3);

            triangle[0].color = sf::Color::Blue;
            triangle[1].color = sf::Color::Blue;
            triangle[2].color = sf::Color(0, 255, 0, 256);

            triangle[0].position = sf::Vector2f(trh->x[0], trh->y[0]);
            triangle[1].position = sf::Vector2f(trh->x[1], trh->y[1]);
            triangle[2].position = sf::Vector2f(trh->x[2], trh->y[2]);
            window->draw(triangle);

            triangle[0].position = sf::Vector2f(trh->x[3], trh->y[3]);
            window->draw(triangle);
        }
};



void fill_trh(struct tetrahed* trh, int* in_x, int* in_y)
{
    for (int i = 0; i < 4; i++)
    {
            trh->x[i] = in_x[i];
            trh->y[i] = in_y[i];
    }
}

void sort_trh(struct tetrahed* trh)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3 - i; j++)
            if (trh->x[j] > trh->x[j + 1])
            {
                std::swap(trh->x[j], trh->x[j + 1]);
                std::swap(trh->y[j], trh->y[j + 1]);
            }

    for (int i = 0; i < 2; i++)
        if (trh->y[2*i] > trh->y[2*i + 1])
            {
                std::swap(trh->x[2*i], trh->x[2*i + 1]);
                std::swap(trh->y[2*i], trh->y[2*i + 1]);
            }
}
