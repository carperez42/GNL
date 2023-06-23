/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:40:06 by carperez          #+#    #+#             */
/*   Updated: 2023/06/17 19:40:06 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *sOri)
{
	if (*sOri != '\0')
		return (ft_strlen(sOri + 1) + 1);
	return (0);
}

//"ft_memliberator" This function frees dynamically allocated memory during
// program execution and initializes the associated header pointer to NULL.
void	ft_memliberator(char **pMemory)
{
	free(*pMemory);
	*pMemory = NULL;
}

void	*ft_memcpy(void *sDest, const void *sOri, size_t nChg)
{
	size_t	ia;

	ia = 0;
	if (sDest != NULL || sOri != NULL)
	{
		while (ia < nChg)
		{
			*((char *)sDest + ia) = *((char *)sOri + ia);
			ia ++;
		}
	}
	return (sDest);
}

//"ft_linebreak_finder" This function checks if the buffer, which it reads from
// the File Descriptor, contains any line breaks.
char	*ft_linebreak_finder(const char *sMainbuff)
{
	while (sMainbuff && *sMainbuff != '\0' && *sMainbuff != '\n')
		sMainbuff ++;
	if (sMainbuff && *sMainbuff == '\n')
		return ((char *) sMainbuff);
	return (NULL);
}

//"ft_rawline_creator" This function accumulates in the buffer, which it reads
// from the File Descriptor, the new information extracted from the last read
// window.
char	*ft_rawline_creator(char *sMainbuff, char const *sWindow)
{
	char	*p_newbuff;
	int		l_front;
	int		l_back;

	p_newbuff = NULL;
	if (sMainbuff)
		l_front = ft_strlen(sMainbuff);
	else
		l_front = 0;
	l_back = ft_strlen(sWindow);
	p_newbuff = malloc (sizeof(char) * (l_front + l_back + 1));
	if (p_newbuff != NULL)
	{
		if (l_front == 0)
			ft_memcpy(p_newbuff, sWindow, l_back + 1);
		else
		{
			ft_memcpy(p_newbuff, sMainbuff, l_front);
			ft_memcpy(&p_newbuff[l_front], sWindow, l_back + 1);
		}
		ft_memliberator(&sMainbuff);
	}
	return (p_newbuff);
}

//END
