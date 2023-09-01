#ifndef		CUB3D_H
# define		CUB3D_H

#define	MAP_PARSET	"10NWES"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <MLX42/MLX42.h>
#include "getnext/get_next_line.h"

typedef struct player
{
	int playersize;
	int Pposy;
	int Pposx;
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


char	*ft_strdup(char *dst, char	*src);
void	saveMap(t_runtime *r, int fd, char *pline);
int		fileNameCheck(char *filename);
void	initval(t_runtime *r);
void	cubfile(t_runtime *r, int fd);
#endif