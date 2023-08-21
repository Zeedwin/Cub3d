/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:18:19 by jgirard-          #+#    #+#             */
/*   Updated: 2023/08/21 13:48:11 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#define WIDTH 300
#define HEIGHT 300
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
	if(!img || x > img->width || y > img->height)
	{
		//r->player.Pposx -= 1;
		//r->player.Pposy -= 2;
		printf("Error: POB!\n");
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

void fillCube(mlx_image_t *img, int x, int y, int size, int fill_color) {
    for (int i = x + 1; i < x + size; i++) {
        for (int j = y - 1; j > y - size; j--) {
            my_mlx_put_pixel(img, j, i, fill_color);
        }
    }
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	//t_player *pl = param;
	t_runtime *r = param;
	
	printf("Pxpos = %d Pypos = %d\n", r->player.Pposx, r->player.Pposy);
	if ((keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) || (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_REPEAT))
	{
		memset(r->img->pixels, 0, r->img->width*r->img->height*4);
		r->player.Pposx += 2;
		fillCube(r->img, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
		//printf("Posx = %d\n", pl->Pposx);
	}
	if ((keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS) || (keydata.key == MLX_KEY_UP && keydata.action == MLX_REPEAT))
	{
		memset(r->img->pixels, 0, r->img->width*r->img->height*4);
		r->player.Pposy -= 2;
		fillCube(r->img, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
		//printf("Posy = %d\n", pl->Pposy);
	}
	if ((keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS) || (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_REPEAT))
	{
		
		memset(r->img->pixels, 0, r->img->width*r->img->height*4);
		r->player.Pposy += 2;
		fillCube(r->img, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
		//printf("Posy = %d\n", pl->Pposy);
	}
	if ((keydata.key == MLX_KEY_LEFT && keydata.action == MLX_REPEAT) || (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS))
	{
		memset(r->img->pixels, 0, r->img->width*r->img->height*4);
		r->player.Pposx -= 2;
		fillCube(r->img, r->player.Pposy- r->player.playersize / 2, r->player.Pposx + r->player.playersize / 2, r->player.playersize ,get_rgba(255, 0, 0, 255));
		//printf("Posy = %d\n", pl->Pposy);
	}
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
	saveMap(&r, fd);
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!mlx)
		ft_error(); 
	r.img = mlx_new_image(mlx, HEIGHT, WIDTH);
	if (!r.img || (mlx_image_to_window(mlx, r.img, 0, 0) < 0))
		ft_error();
	r.player.playersize = 40;
	r.player.Pposx = 250;
	r.player.Pposy = 250;
	fillCube(r.img, r.player.Pposx - r.player.playersize / 2, r.player.Pposy + r.player.playersize / 2, r.player.playersize ,get_rgba(255, 0, 0, 255));
	drawLine(r.img, 20, 20, 50, 50, get_rgba(255, 0, 0, 255));
	mlx_loop_hook(mlx,loop_hook, NULL);
	mlx_key_hook(mlx, &my_keyhook, &r);
	printf("Pxpos = %d Pypos = %d\n", r.player.Pposx, r.player.Pposy);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}