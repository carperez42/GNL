/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:39:51 by carperez          #+#    #+#             */
/*   Updated: 2023/06/17 19:39:51 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//"ft_position_tracker" is a function that captures all the content of the File
// Descriptor from the last performed reading position up to the last window of
// the reading loop where it detects the first line break or reaches the end of
// the file.
static char	*ft_position_tracker(int fd, char *pPosition)
{
	char	*p_buffer;
	int		n_bytes;

	p_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (p_buffer)
	{
		n_bytes = 1;
		while (!ft_linebreak_finder(pPosition) && n_bytes > 0)
		{
			n_bytes = read(fd, p_buffer, BUFFER_SIZE);
			if (n_bytes > 0)
			{
				*(p_buffer + n_bytes) = '\0';
				pPosition = ft_rawline_creator(pPosition, p_buffer);
			}
			else if (n_bytes < 0)
				ft_memliberator(&pPosition);
		}
		ft_memliberator(&p_buffer);
	}
	else
		pPosition = NULL;
	return (pPosition);
}

//"ft_position_tracker" is a function that filters the bytes read from the last
// updated reading position of the File Descriptor until the first line break
// or null character.
static char	*ft_line_processor(char *pPosition)
{
	int		ia;
	char	*p_clean;

	ia = 0;
	p_clean = NULL;
	while (*(pPosition + ia) && *(pPosition + ia) != '\n')
		ia ++;
	p_clean = (char *)malloc(sizeof(char) * (ia + 2));
	if (p_clean)
	{
		ia = 0;
		while (*(pPosition + ia) && *(pPosition + ia) != '\n')
		{
			*(p_clean + ia) = *(pPosition + ia);
			ia ++;
		}
		if (*(pPosition + ia) == '\n')
		{
			*(p_clean + ia) = '\n';
			ia ++;
		}
		*(p_clean + ia) = '\0';
	}
	return (p_clean);
}

//"ft_position_updater" is a function that updates the reading position of
// the File Descriptor based on the last detected line break. It stores
// the updated position in a static pointer and takes into account
// the remaining windowing offset for the next execution of the "get_next_line"
// function.
static char	*ft_position_updater(char *pPosition)
{
	int		ia;
	int		ib;
	char	*p_update;

	ia = 0;
	ib = 0;
	p_update = NULL;
	while (*(pPosition + ia) && *(pPosition + ia) != '\n')
		ia ++;
	if (!((*(pPosition + ia) == '\n' && *(pPosition + 1 + ia) == '\0')
			|| !(*(pPosition + ia))))
	{
		p_update = (char *)malloc(sizeof(char)
				* (ft_strlen(pPosition) - ia + 1));
		if (p_update)
		{
			ia ++;
			while (*(pPosition + ia))
				p_update[ib ++] = pPosition[ia ++];
			*(p_update + ib) = '\0';
		}
	}
	ft_memliberator(&pPosition);
	return (p_update);
}

//"get_next_line" is the primary function from which the reading position of
// the incoming File Descriptor is located and updated. It follows a
// step-by-step process to capture the content up to the next line break and
// returns it. Additionally, it ensures that the reading position is properly
// updated after encountering the last line break, if required. In the case of
// reading multiple different File Descriptors consecutively, it will preserve
// the respective reading positions of each of them stored in a static array
// of pointers.
char	*get_next_line(int fd)
{
	char			*p_line;
	static char		*p_position[MAX_PAGE];

	p_line = NULL;
	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		p_position[fd] = ft_position_tracker(fd, p_position[fd]);
		if (p_position[fd])
		{
			p_line = ft_line_processor(p_position[fd]);
			p_position[fd] = ft_position_updater(p_position[fd]);
		}
	}
	return (p_line);
}

//END
