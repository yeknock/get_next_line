/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:59:22 by ymartiro          #+#    #+#             */
/*   Updated: 2024/04/06 14:59:25 by ymartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	count_beforen(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] != '\n')
		i++;
	return (i);
}

char	*ft_get_line(char *buf)
{
	char	*line;
	char	*tmp_buf;
	char	*ptr;
	int		i;

	i = 0;
	ptr = buf;
	line = malloc(sizeof(char) * count_beforen(buf) + 1);
	tmp_buf = malloc(sizeof(char) * ft_strlen(buf) - count_beforen(buf));
	if (!line || !tmp_buf)
		return (0);
	while (buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';
	i++;
	while (buf[i] != '\0')
	{
		tmp_buf[i - count_beforen(buf) - 1] = buf[i];
		i++;
	}
	tmp_buf[i - count_beforen(buf)] = '\0';
	buf = tmp_buf;
	free(ptr);
	return (line);
}

char	*ft_read(int fd, char *buf)
{
	char	*tmp;
	char	*ptr_buf;
	int		bytes_read;

	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	bytes_read = 1;
	if (!tmp)
		return (0);
	while (!ft_strchr(buf, '\n') && bytes_read)
	{
		ptr_buf = buf;
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(tmp);
			return (0);
		}
		tmp[bytes_read] = '\0';
		buf = ft_strjoin(buf,tmp);
		free(ptr_buf);
	}
	free(tmp);
	return (buf);
}

char	*get_next_line(int fd)
{
	static	char	*buf;
	char			*line;

	if(fd < 0 || BUFFER_SIZE <= 0 || !buf)
		return (0);
	buf = ft_read(fd, buf);
	if (!buf)
		return (0);
	line = ft_get_line(buf);
	


	return (line);
}

int main()
{
	int fd = open("main.txt", O_RDONLY);
	char *p = get_next_line(fd);

	printf("%s", p);
	return (0);
}