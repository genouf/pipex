/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:45:31 by genouf            #+#    #+#             */
/*   Updated: 2022/06/17 16:47:29 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	print_error(char *reason, int fd)
{
	if (errno)
		perror(reason);
	else
		ft_putstr_fd(reason, fd);
	exit(EXIT_FAILURE);
}

void	free_exec(t_exec data_e)
{
	free_split(data_e.cmd);
	if (data_e.free == 1)
		free(data_e.path);
}