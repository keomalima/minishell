/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:01:45 by keomalima         #+#    #+#             */
/*   Updated: 2025/01/01 17:27:20 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*clear_buff(char *buf, char *line, size_t i)
{
	ft_memmove(buf, buf + i + 1, ft_strlen(buf + i + 1) + 1);
	return (line);
}

static char	*get_line(int fd, char *buf, char *line)
{
	size_t	i;
	ssize_t	bytes_read;

	while (1)
	{
		if (!buf[0])
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read == 0)
				return (line);
			if (bytes_read < 0)
				return (clear_line(line));
			buf[bytes_read] = '\0';
		}
		i = 0;
		while (buf[i] && buf[i] != '\n')
			i++;
		line = ft_strnjoin(line, buf, i + (buf[i] == '\n'));
		if (!line)
			return (NULL);
		if (buf[i] == '\n')
			return (clear_buff(buf, line, i));
		ft_bzero(buf, BUFFER_SIZE);
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	return (get_line(fd, buf, line));
}
