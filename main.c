/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:19 by jgirard-          #+#    #+#             */
/*   Updated: 2023/09/04 15:10:34 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#define WIDTH 10
#define HEIGHT 10
#define BPP sizeof(int32_t)
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void my_mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}


int my_mlx_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	//printf("width: %d , lenght: %d\n", img->width, img->height);
	if(!img || x > img->width || y > img->height)
	{
		printf("Error:  gros con POB!\n");
		exit (-1);
	}
	uint8_t *pixelbuff = &img->pixels[(y * img->width + x) * 4];
	my_mlx_draw_pixel(pixelbuff, color);
	return (0);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void drawLine(mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx -dy;
	 while (1) {
        my_mlx_put_pixel(img, y1, x1, color);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
		}
	 }
}

// void drawCube(mlx_image_t *img, int x, int y, int size, int color) {
//     // Draw front face
//     drawLine(img, x, y, x + size, y, color);
//     drawLine(img, x, y, x, y - size, color);
//     drawLine(img, x, y - size, x + size, y - size, color);
//     drawLine(img, x + size, y, x + size, y - size, color);


// }

void draw_line(mlx_image_t *img, int x0, int y0, double angle) {
    // Calculate the endpoint of the line
    int x1 = x0 + (int)(30 * cos(angle));
    int y1 = y0 + (int)(30 * sin(angle));

    // Calculate the differences
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    // Determine the direction of movement along the x and y axes
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int error = dx - dy;
    int current_x = x0;
    int current_y = y0;

    // Loop through the line and draw pixels
    while (1) {
       	my_mlx_put_pixel(img, current_x, current_y, get_rgba(255, 0, 0, 255)); // Set pixel color

        if (current_x == x1 && current_y == y1) {
            break; // Line endpoint reached
        }

        int error2 = error * 2;

        if (error2 > -dy) {
            error -= dy;
            current_x += sx;
        }

        if (error2 < dx) {
            error += dx;
            current_y += sy;
        }
    }
}

void fillCube(t_runtime *r, int x, int y, int size, int fill_color) {
	double rad_raystart;

	rad_raystart = r->player.Pdir + FOV / 2;
    for (int i = x + 1; i < x + size; i++) {
        for (int j = y - 1; j > y - size; j--) {
            my_mlx_put_pixel(r->img, j, i, fill_color);
        }
    }
	while ( )
	{
		/* code */
	}
	
	//draw_line(r->img, r->player.Pposx, r->player.Pposy, r->player.Pdir);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	//t_player *pl = param;
	t_runtime *r = param;
	
	if ((keydata.key == MLX_KEY_D && keydata.action == MLX_REPEAT))
	{
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		r->player.Pposx += 2;
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
		//printf("Posx = %d\n", pl->Pposx);
	}
	if ((keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) || (keydata.key == MLX_KEY_W && keydata.action == MLX_REPEAT))
	{
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		r->player.Pposy -= 2;
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
		//printf("Posy = %d\n", pl->Pposy);
	}
	if ((keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS) || (keydata.key == MLX_KEY_S && keydata.action == MLX_REPEAT))
	{
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		r->player.Pposy += 2;
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
		//printf("Posy = %d\n", pl->Pposy);
	}
	if ((keydata.key == MLX_KEY_A && keydata.action == MLX_REPEAT) || (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS))
	{
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		r->player.Pposx -= 2;
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
		//printf("Posy = %d\n", pl->Pposy);
	}
	if ((keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT))
	{
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		r->player.Pdir += 0.0174533;
		if(r->player.Pdir > 2 * PI)
		{
			r->player.Pdir -= 2 * PI;
		}
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
	}
	if ((keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT) || (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS))
	{
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		r->player.Pdir -= 0.0174533;
		if(r->player.Pdir < 0)
		{
			r->player.Pdir += 2 * PI;
		}
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
	}
	printf("Pxpos = %d Pypos = %d\n", r->player.Pposx, r->player.Pposy);
}

void loop_hook() 
{
		
}

int	main(int ac, char **av)
{
	(void)ac;
	int fd;
	if(fileNameCheck(av[1]))
		return (1);
	fd = open(av[1], O_RDONLY);
	t_runtime r;
	cubfile(&r, fd);
	init_Ppos(&r);
	printf("nb of lines = %d, nb of columns %d\n",r.map.lines, r.map.columns);
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_t* mlx = mlx_init(100 * r.map.columns, 100 * r.map.lines, "cub3D", true);
	if (!mlx)
		ft_error();
	r.img = mlx_new_image(mlx, 100 * r.map.columns, 100 * r.map.lines);
	if (!r.img || (mlx_image_to_window(mlx, r.img, 0, 0) < 0))
		ft_error();
	r.player.playersize = 10;
	r.player.Pposx = 40;
	r.player.Pposy = 40;
	r.player.Pdir = PI;
	fillCube(&r, r.player.Pposx - r.player.playersize / 2, r.player.Pposy + r.player.playersize / 2, r.player.playersize ,get_rgba(255, 0, 0, 255));
	mlx_loop_hook(mlx,loop_hook, NULL);
	mlx_key_hook(mlx, &my_keyhook, &r);
	printf("Pxpos = %d Pypos = %d\n", r.player.Pposx, r.player.Pposy);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}