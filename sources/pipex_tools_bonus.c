/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:31:22 by genouf            #+#    #+#             */
/*   Updated: 2022/06/23 16:29:43 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	init_pipes(int	***pipes, int processes, t_data_pip *data)
{
	int	i;

	i = 0;
	while (i < processes - 1)
	{
		if (pipe((*pipes)[i]) == -1)
			print_error_free("Error\nPipe failed !\n", 2, data);
		i++;
	}
}

void	close_pipes_child(int ***pipes, int processes, int i)
{
	int	j;

	j = 0;
	while (j < processes - 1)
	{
		if (i - 1 != j)
			close((*pipes)[j][0]);
		if (i != j)
			close((*pipes)[j][1]);
		j++;
	}
}

void	free_pp(int **pipes, int *pids)
{
	free(pids);
	free_split((void **)pipes);
}

void	pipex_end(int **pipes, int *pids, int processes, t_data_pip *data)
{
	int	j;
	int	i;

	j = 0;
	while (j < processes - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	i = -1;
	while (++i < processes)
		wait(NULL);
	free_pp(pipes, pids);
	close(data->data_fd.file1);
	close(data->data_fd.file2);
}
