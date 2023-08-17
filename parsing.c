/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:54:12 by jgirard-          #+#    #+#             */
/*   Updated: 2023/08/17 19:41:25 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"
#include <unistd.h>
#include <stdio.h>

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

void	mapParser(int fd, t_runtime *r)
{
	char *line;
	int i;
	int rows;
	
	line = (char *) 1;
	rows = 0;
	while (line)
	{
		line = get_next_line_mod(fd, &rows);
		++rows;
		i = 0;
		while (line && ft_is_space(line[i]))
		{
			
		}
		
	}
	
}

void saveMap(t_runtime *r, int fd)
{
	char	*act_map;
	char	*tmp;
	char 	*line;
	int		bit;

	tmp = ft_strdup(tmp, "");
	while (bit != 0)
	{
		line = get_next_line(fd);		
	}
	r->map = get_next_line(fd);
	printf("%c\n", r->map[0][1]);
} 

int linechecker(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		
	}
	retunr();
}