#ifndef		CUB3D_H
# define		CUB3D_H

#define	MAP_PARSET	"10NWES"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <MLX42/MLX42.h>
#include <math.h>
#include "getnext/get_next_line.h"

#define CASE_SIZE 100
#define PI 3.141592653589793238462643383279502884197
#define FOV 1.0472

typedef struct player
{
	int 	playersize;
	t_point pos;
	int 	Pposy;
	int		Pposx;
	int		Prevy;
	int		Prevx;
	double	Pdir;
}			t_player;

typedef struct raycast
{
	double 	rad_raystart;
	double 	rad_in;
	double 	x;
	double 	y;
	double	dist_to_vertical;
	double	dist_to_horizontal;
}			t_raycast;

typedef struct point
{
	float	x;
	float	y;
}			t_point;


typedef struct s_map
{
	char	**un_pmap;
	char	**pmap;
	int		columns;
	int		lines;
}			t_map;

typedef struct runetime
{
	t_map		map;
	t_player	player;
	mlx_image_t	*img;
	t_raycast	ray;
	mlx_t		*mlx_1;
}			t_runtime;

void 	init_Ppos(t_runtime *r);
int get_rgba(int r, int g, int b, int a);
int my_mlx_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
void fillcubeborder(t_runtime *r);
char	*ft_strdup(char *dst, char	*src);
void	saveMap(t_runtime *r, int fd, char *pline);
int		fileNameCheck(char *filename);
void	init_val(t_runtime *r);
void	cubfile(t_runtime *r, int fd);
#endif