/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 02:22:49 by jgirard-          #+#    #+#             */
/*   Updated: 2022/06/23 02:23:16 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*ft_readline(int fd, char *storage);
size_t		gnl_ft_strlen(char	*str);
char		*gnl_ft_strjoin(char *s1, char *s2);
char		*gnl_ft_strchr(char *s, int c);
char		*get_next_line(int fd);
char		*ft_readtill(char *storage);
char		*ft_readafter(char *storage);

#endif
