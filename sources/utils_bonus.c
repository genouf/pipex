/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:45:31 by genouf            #+#    #+#             */
/*   Updated: 2022/06/23 16:32:36 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	free_split(void **str)
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

void	free_malloc_failed(void **str, int i)
{
	while (i > -1)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

void	free_exec(t_exec data_e)
{
	free_split((void **)data_e.cmd);
	if (data_e.free == 1)
		free(data_e.path);
}

void	print_error(char *reason, int fd)
{
	if (errno)
		perror(reason);
	else
		ft_putstr_fd(reason, fd);
	exit(EXIT_FAILURE);
}

void	print_error_free(char *reason, int fd, t_data_pip *data)
{
	if (errno)
		perror(reason);
	else
		ft_putstr_fd(reason, fd);
	free_pp(data->pipes, data->pids);
	exit(EXIT_FAILURE);
}
