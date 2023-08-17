/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 02:21:53 by jgirard-          #+#    #+#             */
/*   Updated: 2022/06/26 20:25:47 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

size_t	gnl_ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc((sizeof(char)) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc (sizeof(char)
			* (gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free (s1);
	return (str);
}

char	*ft_readtill(char *storage)
{
	char	*till;
	int		i;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] != '\n' && storage[i] != '\0')
		i++;
	till = malloc(sizeof(char) * (i + 2));
	if (!till)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		till[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		till[i] = storage[i];
		i++;
	}	
	till[i] = '\0';
	return (till);
}

char	*ft_readafter(char *storage)
{
	int		i;
	int		j;
	char	*c;

	i = 0;
	while (storage[i] != '\n' && storage[i])
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	if (storage[i] == '\0')
		return (NULL);
	c = malloc(sizeof(char) * (gnl_ft_strlen(storage) - i + 1));
	if (!c)
		return (NULL);
	i++;
	j = 0;
	while (storage[i])
		c[j++] = storage[i++];
	c[j] = '\0';
	free (storage);
	return (c);
}
