#include "drawer.cpp"
#include "math.h"

class player
{
    private:
        int x;
        int y;
        int len = 80;
        int speed = 5;
        int color = 7;

        int scr_len;

    public:
        player(int in_scr_len)
        {
            x = in_scr_len / 2;
            y = in_scr_len / 2;
            scr_len = in_scr_len;
        }

        void draw(class drawer *drw)
        {
            struct tetrahed trh;
            trh.x[0] = x - len / 2;
            trh.y[0] = y - len / 2;
            trh.x[1] = x - len / 2;
            trh.y[1] = y + len / 2;
            trh.x[2] = x + len / 2;
            trh.y[2] = y + len / 2;
            trh.x[3] = x + len / 2;
            trh.y[3] = y - len / 2;
            drw->draw_trh(&trh, color, 1);
        }

        void protect_cord()
        {
            x = std::max(len / 2, std::min(scr_len - len / 2, x));
            y = std::max(len / 2, std::min(scr_len - len / 2, y));
        }

        void moved(char a)
        {
            switch (a)
            {
                case 'w':
                    y -= speed;
                    break;
                case 'd':
                    x += speed;
                    break;
                case 's':
                    y += speed;
                case 'a':
                    x -= speed;
            }
            protect_cord();
        }
};
