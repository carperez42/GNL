/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:40:15 by carperez          #+#    #+#             */
/*   Updated: 2023/06/17 19:40:15 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

//windowing constant
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *sOri);
void	ft_memliberator(char **pMemory);
void	*ft_memcpy(void *sDest, const void *sOri, size_t nChg);
char	*ft_linebreak_finder(const char *sMainbuff);
char	*ft_rawline_creator(char *sMainbuff, char const *sWindow);
#endif