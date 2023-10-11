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
#define HEIGHT 1080
#define WIDTH 1920
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

void draw_line_r(t_runtime *game, int x0, int y0, double angle) {
    int x1 = x0 + (int)(60 * cos(angle) * WIDTH);
    int y1 = y0 + (int)(60 * sin(angle) * HEIGHT);
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
		if (x0 < 0 || x0 >= WIDTH || y0 < 0 || y0 >= HEIGHT) {
            break;
        }
			// my_mlx_put_pixel(game->img, game->player.Prevx, game->player.Prevy, get_rgba(0, 0, 0, 0));
      		my_mlx_put_pixel(game->img, x0, y0, get_rgba(0, 255, 0, 255));
			// game->player.Prevx = x0;
			// game->player.Prevy = 
        if (x0 == x1 && y0 == y1) break;

        e2 = err;

        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_line(mlx_image_t *img, int x0, int y0, double angle) {
    int x1 = x0 + (int)(60 * cos(angle) * 100);
    int y1 = y0 + (int)(60 * sin(angle) * 100);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int error = dx - dy;
    int current_x = x0;
    int current_y = y0;

    while (1) {
       	my_mlx_put_pixel(img, current_x, current_y, get_rgba(255, 0, 0, 255));

        if (current_x == x1 && current_y == y1) {
            break;
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

void	find_raydist(t_runtime *r)
{
	r->ray.x = cos(r->ray.rad_raystart);
	r->ray.y = sin(r->ray.rad_raystart);
	if (r->ray.y < 0)
	{
		r->ray.dist_to_horizontal = r->player.Pposy  - (r->player.Pposy / CASE_SIZE) * CASE_SIZE;
	}
	if (r->ray.y > 0)
	{
		r->ray.dist_to_horizontal = (r->player.Pposy / CASE_SIZE) * CASE_SIZE + CASE_SIZE - r->player.Pposy;
	}
	if (r->ray.x < 0)
	{
		r->ray.dist_to_vertical = r->player.Pposx - (r->player.Pposx / CASE_SIZE) * CASE_SIZE;	
	}
	if (r->ray.x > 0)
	{
		r->ray.dist_to_vertical = (r->player.Pposx / CASE_SIZE) * CASE_SIZE + CASE_SIZE - r->player.Pposx;
	}
}

void fillCube(t_runtime *r, int x, int y, int size, int fill_color) {
	int i;
	///double endpoint_x = r->player.Pposx + (int)(60 * cos(r->player.Pdir));
    //double endpoint_y = r->player.Pposy + (int)(60* sin(r->player.Pdir));
	i = 0;
	r->ray.rad_in = FOV / WIDTH;
	r->ray.rad_raystart = r->player.Pdir + FOV / 2;
    for (int i = x + 1; i < x + size; i++) {
        for (int j = y - 1; j > y - size; j--) {
            my_mlx_put_pixel(r->img, j, i, fill_color);
        }
    }
	printf("Horizontal = %d , Vertical = %d\n", (int)r->ray.dist_to_horizontal, (int)r->ray.dist_to_vertical);
	while (i  < WIDTH)
	{
		find_raydist(r);
		//draw_line(r->img, r->player.Pposx, r->player.Pposy, r->ray.rad_raystart);
			draw_line_r(r, r->player.Pposx, r->player.Pposy, r->ray.rad_raystart);
		//draw_line_r(r, r->player.Pposx, r->player.Pposy, WIDTH, HEIGHT);
		r->ray.rad_raystart -= r->ray.rad_in;
		i++;
	}
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	//t_player *pl = param;
	t_runtime *r = param;
	
	(void) keydata;
	if (mlx_is_key_down(r->mlx_1, MLX_KEY_D))
	{
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(0, 0, 0, 0));
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		fillcubeborder(r);
		r->player.Pposx += 10;
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
	}
	if (mlx_is_key_down(r->mlx_1, MLX_KEY_W))
	{
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(0, 0, 0, 0));
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		fillcubeborder(r);
		r->player.Pposy -= 10;
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
	}
	if (mlx_is_key_down(r->mlx_1, MLX_KEY_S))
	{
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(0, 0, 0, 0));
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		fillcubeborder(r);
		r->player.Pposy += 10;
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
	}
	if (mlx_is_key_down(r->mlx_1, MLX_KEY_A))
	{
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(0, 0, 0, 0));
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		fillcubeborder(r);
		r->player.Pposx -= 10;
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
	}
	if (mlx_is_key_down(r->mlx_1, MLX_KEY_RIGHT))
	{
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(0, 0, 0, 0));
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		fillcubeborder(r);
		r->player.Pdir += 0.0174533 * 5;
		if(r->player.Pdir > 2 * PI)
		{
			r->player.Pdir -= 2 * PI;
		}
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
	}
	if (mlx_is_key_down(r->mlx_1, MLX_KEY_LEFT))
	{
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(0, 0, 0, 0));
		memset(r->img->pixels, 0, r->img->width *r->img->height * sizeof(int32_t));
		fillcubeborder(r);	
		r->player.Pdir -= 0.0174533 * 5;
		if(r->player.Pdir < 0)
		{
			r->player.Pdir += 2 * PI;
		}
		fillCube(r, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
	}
	//printf("Pxpos = %d Pypos = %d\n", r->player.Pposx, r->player.Pposy);
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
	init_val(&r);
	cubfile(&r, fd);
	//init_Ppos(&r);
	mlx_set_setting(MLX_MAXIMIZED, false);
	r.mlx_1 = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!r.mlx_1)
		ft_error();
	r.img = mlx_new_image(r.mlx_1, WIDTH, HEIGHT);
	if (!r.img || (mlx_image_to_window(r.mlx_1, r.img, 0, 0) < 0))
		ft_error();
	r.player.playersize = 10;
	r.player.Pposx = 270;
	r.player.Pposy = 270;
	r.player.Pdir = PI;
	printf("nb of lines = %d, nb of columns %d\n",r.map.lines, r.map.columns);
	fillcubeborder(&r);
	fillCube(&r, r.player.Pposx - r.player.playersize / 2, r.player.Pposy + r.player.playersize / 2, r.player.playersize ,get_rgba(255, 0, 0, 255));
	mlx_loop_hook(r.mlx_1,loop_hook, &r);
	mlx_key_hook(r.mlx_1, &my_keyhook, &r);
	//printf("Pxpos = %d Pypos = %d\n", r.player.Pposx, r.player.Pposy);
	mlx_loop(r.mlx_1);
	mlx_terminate(r.mlx_1);
	return (EXIT_SUCCESS);
}