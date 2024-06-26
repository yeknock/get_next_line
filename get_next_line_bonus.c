/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:00:01 by ymartiro          #+#    #+#             */
/*   Updated: 2024/04/16 21:00:05 by ymartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

char	*regulator(char *buf, char *line)
{
	char	*tmp_buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
	tmp_buf = malloc(sizeof(char) * (ft_strlen(buf) - i));
	if (!tmp_buf)
		return (0);
	while (buf && buf[i] && buf[i] != '\0')
	{
		i++;
		tmp_buf[j] = buf[i];
		j++;
	}
	free(buf);
	if (line && !line[0])
		free(line);
	return (tmp_buf);
}

char	*ft_get_line(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf && buf[i] == '\n')
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *buf)
{
	char	*tmp;
	char	*ptr_buf;
	int		bytes_read;

	ptr_buf = 0;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	bytes_read = 1;
	if (!tmp)
		return (0);
	while ((!buf || !ft_strchr(buf, '\n')) && bytes_read)
	{
		ptr_buf = buf;
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(tmp);
			free(buf);
			return (0);
		}
		tmp[bytes_read] = '\0';
		buf = ft_strjoin(buf, tmp);
		free(ptr_buf);
	}
	free(tmp);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = 0;
	buf[fd] = ft_read(fd, buf[fd]);
	if (!buf[fd] || buf[fd][0] == '\0')
	{
		free(buf[fd]);
		buf[fd] = 0;
		return (0);
	}
	line = ft_get_line(buf[fd]);
	buf[fd] = regulator(buf[fd], line);
	return (line);
}