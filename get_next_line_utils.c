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

char	*ft_linebreak_finder(const char *sOri)
{
	while (sOri && *sOri != '\0' &&  *sOri != '\n')
		sOri ++;
	if (sOri && *sOri == '\n')
		return ((char *) sOri);
	return (NULL);
}

char	*ft_rawline_creator(char const *sFront, char const *sBack)
{
	char	*p_new;
	int		l_front;
	int		l_back;

	p_new = NULL;
	if (sFront)
		l_front = ft_strlen(sFront);
	else
		l_front = 0;
	l_back = ft_strlen(sBack);
	p_new = malloc (sizeof(char) * (l_front + l_back + 1));
	if (p_new != NULL)
	{
		if (l_front == 0)
			ft_memcpy(p_new, sBack, l_back + 1);
		else
		{
			ft_memcpy(p_new, sFront, l_front);
			ft_memcpy(&p_new[l_front], sBack, l_back + 1);
		}
		free ((char *)sFront);
	}
	return (p_new);
}

