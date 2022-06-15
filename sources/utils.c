/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:45:31 by genouf            #+#    #+#             */
/*   Updated: 2022/06/15 23:01:57 by genouf           ###   ########.fr       */
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

int	check_path_access(t_data *data, char *cmd, int *choice, int increment)
{
	if (access(cmd, F_OK != 0))
	{
		if (strncmp(cmd, "./", 2) != 0)
			*choice += increment;
		else
			return (-1);
	}
	else
	{
		if (increment == 1)
			data->path1 = cmd;
		if (increment == 2)
			data->path2 = cmd;
	}
	return (0);
}
