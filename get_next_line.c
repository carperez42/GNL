/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:40:11 by carperez          #+#    #+#             */
/*   Updated: 2023/06/17 19:40:11 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//"ft_position_tracker" This function reads from the File Descriptor as many
// times as necessary if the read window is smaller than its maximum size,
// until it finds the first newline or reaches the end of the file. For each
// new read, it accumulates the newly read information in the buffer.
static char	*ft_position_tracker(int fd, char *pMainbuff)
{
	char	*p_auxbuff;
	int		n_bytes;

	p_auxbuff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (p_auxbuff)
	{
		n_bytes = 1;
		while (!ft_linebreak_finder(pMainbuff) && n_bytes > 0)
		{
			n_bytes = read(fd, p_auxbuff, BUFFER_SIZE);
			if (n_bytes > 0)
			{
				*(p_auxbuff + n_bytes) = '\0';
				pMainbuff = ft_rawline_creator(pMainbuff, p_auxbuff);
			}
			else if (n_bytes < 0)
				ft_memliberator(&pMainbuff);
		}
		ft_memliberator(&p_auxbuff);
	}
	else
		pMainbuff = NULL;
	return (pMainbuff);
}

//"ft_position_tracker" this function filters the bytes read from the last
// updated reading position of the File Descriptor until the first line break
// or null character.
static char	*ft_line_processor(char *pMainbuff)
{
	int		ia;
	char	*p_line;

	ia = 0;
	p_line = NULL;
	while (*(pMainbuff + ia) && *(pMainbuff + ia) != '\n')
		ia ++;
	p_line = (char *)malloc(sizeof(char) * (ia + 2));
	if (p_line)
	{
		ia = 0;
		while (*(pMainbuff + ia) && *(pMainbuff + ia) != '\n')
		{
			*(p_line + ia) = *(pMainbuff + ia);
			ia ++;
		}
		if (*(pMainbuff + ia) == '\n')
		{
			*(pMainbuff + ia) = '\n';
			ia ++;
		}
		*(p_line + ia) = '\0';
	}
	return (p_line);
}

//"ft_position_updater" this function updates the reading position of
// the File Descriptor based on the last detected line break. It stores
// the updated position in a static pointer and takes into account
// the remaining windowing offset for the next execution of the "get_next_line"
// function.
static char	*ft_position_updater(char *pMainbuff)
{
	int		ia;
	int		ib;
	char	*p_fdspots;

	ia = 0;
	ib = 0;
	p_fdspots = NULL;
	while (*(pMainbuff + ia) && *(pMainbuff + ia) != '\n')
		ia ++;
	if (!((*(pMainbuff + ia) == '\n' && *(pMainbuff + 1 + ia) == '\0')
			|| !(*(pMainbuff + ia))))
	{
		p_fdspots = (char *)malloc(sizeof(char)
				* (ft_strlen(pMainbuff) - ia + 1));
		if (p_fdspots)
		{
			ia ++;
			while (*(pMainbuff + ia))
				p_fdspots[ib ++] = pMainbuff[ia ++];
			*(p_fdspots + ib) = '\0';
		}
	}
	ft_memliberator(&pMainbuff);
	return (p_fdspots);
}

//"get_next_line" is the primary function from which the reading position of
// the incoming File Descriptor is located and updated. It follows a
// step-by-step process to capture the content up to the next line break and
// returns it. Additionally, it ensures that the reading position is properly
// updated after encountering the last line break, if required.
char	*get_next_line(int fd)
{
	char			*p_newline;
	static char		*p_fdspot;

	p_newline = NULL;
	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		p_fdspot = ft_position_tracker(fd, p_fdspot);
		if (p_fdspot)
		{
			p_newline = ft_line_processor(p_fdspot);
			p_fdspot = ft_position_updater(p_fdspot);
		}
	}
	return (p_newline);
}

//END