#include "Cub3d.h"

void fillcubeborder(t_runtime *r)
{
    int i;
    int j;
    int x;
    int y;

    x = 15;
    i = 0;
    while(r->map.un_pmap[i])
    {
        y = 250;
        j = 0;
        while(r->map.un_pmap[i][j])
        {
            for (int k = x; k <= x + CASE_SIZE; k++) {
                for (int l = y; l >= y - CASE_SIZE; l--) {
                    my_mlx_put_pixel(r->img, l, k, get_rgba(105, 105, 105, 255));
                }
            }
            if (r->map.un_pmap[i][j] == '1')
            {
                for (int k = x + 2; k <= x + CASE_SIZE; k++) {
                    for (int l = y - 2; l >= y - CASE_SIZE; l--) {
                        my_mlx_put_pixel(r->img, l, k, get_rgba(255, 255, 255, 255));
                    }
                }
            }
            else if (r->map.un_pmap[i][j] != '1')
            {
                for (int k = x + 2; k <= x + CASE_SIZE; k++) {
                    for (int l = y - 2; l >= y - CASE_SIZE; l--) {
                        my_mlx_put_pixel(r->img, l, k, get_rgba(0, 0, 0, 255));
                    }
                }
            }
            y += 100;
            j++;
        }
        i++;
        x += 100;
    }
}

void check_border(t_runtime *r)
{
    
}