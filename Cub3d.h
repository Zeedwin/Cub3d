#ifndef		CUB3D_H
# define		CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <MLX42/MLX42.h>
#include "getnext/get_next_line.h"

typedef struct s_data
{
	char	**map;
	int		lines;
	int		colums;	
}				t_map;

typedef struct player
{
	int playersize;
	int Pposy;
	int Pposx;
}			t_player;

typedef struct runetime
{
	t_map	map;
	t_player player;
	mlx_image_t	*img;
}			t_runtime;

typedef struct s_map
{
	char	**un_pmap;
	char	**pmap;
	int		columns;
	int		lines;
}			t_map;

char	*ft_strdup(char *dst, char	*src);
void	saveMap(t_runtime *r, int fd, char *pline);
int		fileNameCheck(char *filename);
void	initval(t_runtime *r);
#endif