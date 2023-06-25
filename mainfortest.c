/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainfortest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 10:54:37 by carperez          #+#    #+#             */
/*   Updated: 2023/06/25 11:06:01 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line_bonus.h"
#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int	fd;
	char *line = NULL;

	fd = open("file.txt", O_RDONLY);
	if (fd >= 0)
	{
		while (line)
		{
			line = get_next_line(fd);
			if (line)
				printf("%s", line);
			ft_memliberator(line);
		}
	}
	else
		return (1);
	close(fd);
	return (0);
}

int main()
{
	int fd;
	int	fd2;
	int fd3;
	char *line, *line2, *line3 = NULL;

	fd = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	fd3 = open("file3.txt", O_RDONLY);
	if (!(fd == -1 || fd2 == -1 || fd3 == -1))
	{
		while (line && line2 && line3)
		{
			line = get_next_line(fd);
			line2 = get_next_line(fd2);
			line3 = get_next_line(fd3);
			if (line)
				printf("%s", line);
			if (line2)				
				printf("%s", line2);
			if (line3)				
				printf("%s", line3);
			ft_memliberator(line);
			ft_memliberator(line2);
			ft_memliberator(line3);
		}
	}
	else
		return (1);
	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}