/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:55:09 by jgirard-          #+#    #+#             */
/*   Updated: 2022/06/23 02:10:44 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*line;
	static char		*storage;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	storage = ft_readline(fd, storage);
	if (!storage)
		return (NULL);
	line = ft_readtill(storage);
	storage = ft_readafter(storage);
	return (line);
}

char	*ft_readline(int fd, char *storage)
{	
	int		byread;
	char	*buf;

	buf = malloc ((sizeof(char) * BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byread = 1;
	while (byread != 0 && gnl_ft_strchr(storage, '\n') == 0)
	{
		byread = read(fd, buf, BUFFER_SIZE);
		if (byread == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[byread] = '\0';
		storage = gnl_ft_strjoin(storage, buf);
	}
	free (buf);
	return (storage);
}

char	*gnl_ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = gnl_ft_strlen(s) + 1;
	while (i--)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	return (0);
}
