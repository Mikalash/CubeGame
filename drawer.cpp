#include <SFML/Graphics.hpp>

struct tetrahed
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

        int color[7][3] = {
        {255, 255, 255},//0 - white
        {255, 0,   0},  //1 - red
        {255, 0,   255},//2 - fuchsia
        {0,   255, 0},  //3 - lime
        {255, 255, 0},  //4 - yellow
        {0,   0,   255},//5 - blue
        {0,   255, 255},//6 - aqua
        };
    public:
        drawer(sf::RenderWindow *in_window)
        {
            window = in_window;
        }

        void draw_trh(struct tetrahed* trh, int clr, float bright)
        {
            sort_trh(trh);

            sf::VertexArray triangle(sf::Triangles, 3);

            sf::Color sfml_clr(color[clr][0] * bright, color[clr][1] * bright, color[clr][2] * bright);
            for (int i = 0; i < 3; i++)
                triangle[i].color = sfml_clr;

            for (int i = 0; i < 3; i++)
                triangle[i].position = sf::Vector2f(trh->x[i], trh->y[i]);
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
