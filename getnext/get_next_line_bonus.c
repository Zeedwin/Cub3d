/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 02:18:19 by jgirard-          #+#    #+#             */
/*   Updated: 2022/06/26 20:18:49 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char			*line;
	static char		*storage[4096];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	storage[fd] = ft_readline(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = ft_readtill(storage[fd]);
	storage[fd] = ft_readafter(storage[fd]);
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
