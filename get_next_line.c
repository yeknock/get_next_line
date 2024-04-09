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





void gnl(int fd)
{
	char	*buf;
	int		count;

	count = 0;
	// if (!BUFFER_SIZE)
		// return (0);
	buf = malloc(BUFFER_SIZE);
	while(read(fd, buf, BUFFER_SIZE))
	{
		printf("%s\n", buf);
	}
	// return (count);
}

int main()
{
	int fd = open("main.txt", O_RDONLY);
	gnl(fd);
	// printf("%d", a);

	return (0);
}