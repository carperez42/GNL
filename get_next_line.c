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

static int	ft_position_tracker(int fd, char **pPosition)
{
	char	*p_buffer;
	int		n_bytes;

	p_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (p_buffer)
	{
		while (!ft_linebreak_finder(*pPosition) && n_bytes > 0)
		{
			n_bytes = read(fd, p_buffer, BUFFER_SIZE);
			if (n_bytes > 0)
			{
				p_buffer[n_bytes] = '\0';
				*pPosition = ft_rawline_creator(*pPosition, p_buffer);
			}
			else if (n_bytes < 0)
				*pPosition = NULL;
		}
		free (p_buffer);
	}
	else
		*pPosition = NULL;
	return (n_bytes);
}

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

static char	*ft_position_updater(char *pPosition, int fEnd)
{
	int		ia;
	int		ib;
	char	*p_update;

	ia = 0;
	ib = 0;
	p_update = NULL;
	if (fEnd)
	{
		while (*(pPosition + ia) && *(pPosition + ia) != '\n')
			ia ++;
		p_update = (char *)malloc(sizeof(char)
				* (ft_strlen(pPosition) - ia + 1));
		if (p_update)
		{
			ia ++;
			while (*(pPosition + ia))
				p_update[ib ++] = pPosition[ia ++];
			p_update[ib] = '\0';
		}
	}
	free (pPosition);
	return (p_update);
}

char	*get_next_line(int fd)
{
	int				f_end;
	char			*p_line;
	static char		*p_position;

	f_end = 1;
	p_line = NULL;
	if (fd >= 0 && BUFFER_SIZE > 0)
	{
		f_end = ft_position_tracker(fd, &p_position);
		if (p_position)
		{
			p_line = ft_line_processor(p_position);
			p_position = ft_position_updater(p_position, f_end);
		}
	}
	return (p_line);
}