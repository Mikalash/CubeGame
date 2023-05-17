#include "masks.cpp"
#include "drawer.cpp"

class segment
{
    private:
        int z;//z cord of sigment
        int color = 0;
        int z_len = 200;//z_len of sigment
        int z_speed = 5;

        int z_view = 800;//camera cord * -1
        int scr_len;
        int mask_index;

    public:
        segment()
        {}

        void sg_fill(int number, int in_scr_len, int in_color, int in_mask_index)
        {
            z = number * z_len;
            scr_len = in_scr_len;
            color = in_color;
            mask_index = in_mask_index;
        }

        int get_cord_scr(int x, int z)
        {
            x = x - scr_len / 2;

            int cord_on_scr = z_view * x / (z + z_view);
            cord_on_scr += scr_len / 2;

            return cord_on_scr;
        }

        void draw_brd(class drawer *drw)
        {
            struct tetrahed trh;
            for (int i = 0; i < 2; i ++)
            {
                for (int j = 0; j < 4; j ++)
                {
                    trh.x[j] = get_cord_scr(i * scr_len, z + (j / 2) * z_len);
                    trh.y[j] = get_cord_scr((j % 2) * scr_len, z + (j / 2) * z_len);
                }
                drw->draw_trh(&trh, color, (1 - 0.2) * (1 - z / 2600.0));
            }
            for (int i = 0; i < 2; i ++)
            {
                for (int j = 0; j < 4; j ++)
                {
                    trh.x[j] = get_cord_scr((j % 2) * scr_len, z + (j / 2) * z_len);
                    trh.y[j] = get_cord_scr(i * scr_len, z + (j / 2) * z_len);
                }
                drw->draw_trh(&trh, color, (1 - 0.1) * (1 - z / 2600.0));
            }
        }

        void draw_srf(class drawer *drw)
        {
            struct tetrahed trh;
            for (int i = 0; i < 6; i++)
                for (int j = 0; j < 6; j++)
                    if (mask[mask_index][i][j] == 1)
                    {
                        trh.x[0] = get_cord_scr(j * scr_len / L_MASKS, z + z_len);
                        trh.y[0] = get_cord_scr(i * scr_len / L_MASKS, z + z_len);
                        trh.x[1] = get_cord_scr(j * scr_len / L_MASKS, z + z_len);
                        trh.y[1] = get_cord_scr((i + 1) * scr_len / L_MASKS, z + z_len);
                        trh.x[2] = get_cord_scr((j + 1) * scr_len / L_MASKS, z + z_len);
                        trh.y[2] = get_cord_scr((i + 1) * scr_len / L_MASKS, z + z_len);
                        trh.x[3] = get_cord_scr((j + 1) * scr_len / L_MASKS, z + z_len);
                        trh.y[3] = get_cord_scr(i * scr_len / L_MASKS, z + z_len);
                        drw->draw_trh(&trh, color, 1 * (1 - (z + z_len) / 2800.0));
                        //2 / (1 + exp(z / 500))
                    }
        }

        void draw(class drawer *drw)
        {
            draw_brd(drw);
            draw_srf(drw);
        }

        bool go_ahead()
        {
            z -= z_speed;
            if (z < -z_len)
                return 1;
            return 0;
        }

        void respawn(int number_of_segments)
        {
            z = (number_of_segments - 1) * z_len  - z_speed;
            mask_index = gen_index();
        }

        int get_mask_index()
        {
            return mask_index;
        }
};
