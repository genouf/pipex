/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:44:39 by genouf            #+#    #+#             */
/*   Updated: 2022/06/03 12:10:43 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* INCLUDE */
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# include "../libft/libft.h"

char	*get_next_line(int fd);
void	ft_substr_gnl(char *s, unsigned int start, char *save);
void	ft_splitbuff(char **buff, char **result, int id_line);
char	*ft_subuff(char *buff, int id_line);
void	*ft_calloc(size_t count, size_t size);

#endif
