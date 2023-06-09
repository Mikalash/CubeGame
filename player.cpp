#include "drawer.cpp"
#include "masks.cpp"
#include "math.h"

class player
{
    private:
        int x;
        int y;
        int len = 80;
        int speed = 10;
        int bonus = 0;
        int color = 7;

        int scr_len;
        int lifes = 3;
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
            drw->draw_lifes(x - len / 2, y - len / 2, lifes);
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
                    y -= speed + bonus;
                    break;
                case 'd':
                    x += speed + bonus;
                    break;
                case 's':
                    y += speed + bonus;
                    break;
                case 'a':
                    x -= speed + bonus;
                    break;
            }
            protect_cord();
        }

        void calc_bonus(float score)
        {
            bonus = score / 0.1;
        }

        bool is_crash(int mask_index)
        {
            int i_len = scr_len / L_MASKS;
            int p_len = len / 2 - 1;

            if (mask[mask_index][(y - p_len)/i_len][(x - p_len)/i_len] == 1)
            {
                lifes--;
                return 1;
            }
            if (mask[mask_index][(y - p_len)/i_len][(x + p_len)/i_len] == 1)
            {
                lifes--;
                return 1;
            }
            if (mask[mask_index][(y + p_len)/i_len][(x + p_len)/i_len] == 1)
            {
                lifes--;
                return 1;
            }
            if (mask[mask_index][(y + p_len)/i_len][(x - p_len)/i_len] == 1)
            {
                lifes--;
                return 1;
            }
            return 0;
        }

        int get_lifes()
        {
            return lifes;
        }
};
