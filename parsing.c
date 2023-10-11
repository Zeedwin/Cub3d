/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:54:12 by jgirard-          #+#    #+#             */
/*   Updated: 2023/09/04 14:38:54 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>

char *ft_strdup(char	*dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
		++i;
	dst = malloc(sizeof(char) * i + 1);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

static int	ft_mots(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			j++;
			while (str[i] && str[i] != c)
			i++;
		}
	}
	return (j);
}

static char	*ft_mettre(char *mot, char const *s, int i, int len)
{
	int	j;

	j = 0;
	while (len > 0)
	{
		mot[j] = s[i - len];
		j++;
		len--;
	}
	mot[j] = '\0';
	return (mot);
}

static char	**ft_sep(char const *s, char c, char **s2, int num)
{
	int	i;
	int	mot;
	int	len;

	i = 0;
	mot = 0;
	len = 0;
	while (mot < num)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		s2[mot] = (char *)malloc(sizeof(char) * (len + 1));
		if (!s2)
			return (0);
		ft_mettre(s2[mot], s, i, len);
		len = 0;
		mot++;
	}
	s2[mot] = NULL;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num;

	if (!s)
		return (0);
	num = ft_mots(s, c);
	s2 = (char **)malloc(sizeof(char *) * (num + 1));
	if (!s2)
		return (0);
	ft_sep(s, c, s2, num);
	return (s2);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char			*s3;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)malloc(sizeof(*s3) * (gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = 0;
	return (s3);
}

char	*ft_strdup_f(char *src)
{
	int		i;
	char	*p;

	i = 0;
	p = malloc((gnl_ft_strlen(src) + 1) * sizeof(char));
	if (!p)
		return (0);
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_strcpy_env(char **envp)
{
	int		i;
	char	**cpyenv;

	i = 0;
	cpyenv = NULL;
	while (envp[i])
	{
		cpyenv[i] = ft_strdup_f(envp[i]);
		i++;
	}
	cpyenv[i] = NULL;
	return (cpyenv);
}

int fileNameCheck(char *filename)
{
	int i;

	i = 0;
	if(!filename)
	{
		printf("Error: No file was passed, Exmple: ./cub3D <filename>\n");
		return (1);
	}
	while(filename[i])
		i++;
	if(filename[i - 1] == 'b' && filename[i - 2] == 'u' && filename[i - 3] == 'c')
		return(0);
	printf("Error: Wrong filetype, select a file with .cub termination\n");
	return(1);
}

int ft_is_space(int n)
{
	return(n == '\r' 
		|| n == ' ' 
		|| n == '\t'
		|| n == '\0'
		|| n == '\v');
}

int	is_line_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_is_space(str[i++]))
			return (0);
	}
	return (1);
}


// void	mapParser(int fd, t_runtime *r)
// {
// 	char *line;
// 	int i;
// 	int rows;
	
// 	line = (char *) 1;
// 	rows = 0;
// 	while (line)
// 	{
// 		line = get_next_line_mod(fd, &rows);
// 		++rows;
// 		i = 0;
// 		while (line && ft_is_space(line[i]))
// 		{
			
// 		}
		
// 	}
	
// }

void	init_val(t_runtime *r)
{
	r->map.lines = 0;
	r->map.columns = 0;
	r->map.un_pmap = NULL;
	r->map.pmap = NULL;
	r->player.playersize = 0;
	r->player.Pposx = 0;
	r->player.Pposy = 0;
	r->player.Prevx = 0;
	r->player.Prevy = 0;
}

void saveMap(t_runtime *r, int fd, char *pline)
{
	char	*n_map;
	char	*tmp;
	
	printf("lal\n");
	tmp = NULL;
	n_map = ft_strdup(tmp, "");
	while (pline && !is_line_empty(pline))
	{
		n_map = ft_strjoin(n_map, pline);
		free(pline);
		pline =	get_next_line(fd);
		r->map.lines++;
		if((int) gnl_ft_strlen(pline) > r->map.columns)
			r->map.columns = gnl_ft_strlen(pline);
	}
	free(pline);
	//r->map.un_pmap = ft_be
	r->map.un_pmap = ft_split(n_map, '\n');
	int i = 0;
	while (r->map.un_pmap[i])
	{
		printf("line numb %d = %s\n",i ,  r->map.un_pmap[i]);
		i++;
	}
	
	free(n_map);
} 

char	*get_next_mod(int fd, int *line_num)
{
	char	*line;
	int		nb_line;

		printf("yey\n");
	line = get_next_line(fd);
	//if(line == NULL)
	//	exit (0);
	nb_line = 1;
	while (line && is_line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
		printf("line %s\n", line);
		nb_line++;
	}
	if (line_num)
		line_num += nb_line;
	return (line);
}

int ft_isupcase(int c)
{
	if(c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int charset(char c, char *set)
{
	int i;

	i = 0;
	while(set[i])
	{
		if(c == set[i++])
			return (1);
	}
	printf("i have down syndrome\n");
	return (0);
}

// void	mapParser(int fd, t_runtime *r)
// {
// 	char *line;
// 	int i;
// 	int rows;
	
// 	line = (char *) 1;
// 	rows = 0;
// 	while (line)
// 	{
// 		line = get_next_line_mod(fd, &rows);
// 		++rows;
// 		i = 0;
// 		while (line && ft_is_space(line[i]))
// 		{
			
// 		}
		
// 	}
	
// }

// rad_raystart = Pdir + FOV / 2

void 	init_Ppos(t_runtime *r)
{
	int y;
	int x;
	int c;

	y = 0;
	x = 0;
	c = CASE_SIZE;
	printf("ALAIDE %c\n", r->map.un_pmap[y][x]);
	while (r->map.un_pmap[y])
	{
		while (r->map.un_pmap[y][x])
		{
			if (r->map.un_pmap[y][x] == charset(r->map.un_pmap[y][x], MAP_PARSET))
			{
				r->player.Pposx = x * c + 1 * c / 2;
				r->player.Pposy = y * c + 1 * c / 2;
				return;
			}
			x++;
		}
		y++;
	}
}

void	cubfile(t_runtime *r, int fd)
{
	char	*uline;
	int		i;

	printf("col check = %d\n", r->map.columns);
	uline = (char *) 1;
	while (uline && !r->map.un_pmap)
	{
		uline = get_next_mod(fd, &r->map.lines);
		r->map.lines++;
		i = 0;
		while (uline && ft_is_space(uline[i]))
			i++;
		if (!uline || uline[i] == '#')
			free(uline);
		//else if (ft_isupcase(uline[i]))
		//	map_params_setup(uline, r);
		else if (charset(uline[i], MAP_PARSET))
			saveMap(r, fd, uline);
		else
			printf("Error: Critical 102\n");
	}
	//uline = get_next_mod(fd, &r->map.lines);
	if(!uline)
		printf("Error: Critical 101\n");
}