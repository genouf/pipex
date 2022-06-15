/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:45:31 by genouf            #+#    #+#             */
/*   Updated: 2022/06/15 11:24:39 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	free_path(t_data *data)
{
	free_split(data->cmd1);
	free_split(data->cmd2);
	free(data->path1);
	free(data->path2);
}

void	print_error(t_data *data, char *reason, int fd, int mode)
{
	if (mode == 0)
	{
		ft_putstr_fd(reason, fd);
		exit(EXIT_FAILURE);
	}
	else
	{
		free_path(data);
		ft_putstr_fd(reason, fd);
		exit(EXIT_FAILURE);
	}
}
