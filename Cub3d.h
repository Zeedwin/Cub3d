#ifndef		CUB3D_H
# define		CUB3D_H

#define	MAP_PARSET	"10NWES"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <MLX42/MLX42.h>
#include <math.h>
#include "getnext/get_next_line.h"

#define CASE_SIZE 20;
#define PI 3.141592653589793238462643383279502884197
#define FOV 1.0472

typedef struct player
{
	int 	playersize;
	int 	Pposy;
	int 	Pposx;
	double	Pdir;
}			t_player;

typedef struct s_map
{
	char	**un_pmap;
	char	**pmap;
	int		columns;
	int		lines;
}			t_map;

typedef struct runetime
{
	t_map	map;
	t_player player;
	mlx_image_t	*img;
}			t_runtime;

void 	init_Ppos(t_runtime *r);
char	*ft_strdup(char *dst, char	*src);
void	saveMap(t_runtime *r, int fd, char *pline);
int		fileNameCheck(char *filename);
void	initval(t_runtime *r);
void	cubfile(t_runtime *r, int fd);
#endif