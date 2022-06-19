/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:31:22 by genouf            #+#    #+#             */
/*   Updated: 2022/06/19 16:18:20 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	init_pipes(int	***pipes, int processes)
{
	int	i;

	i = 0;
	while (i < processes - 1)
	{
		if (pipe((*pipes)[i]) == -1)
			print_error("Error\nPipe failed !\n", 2);
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

void	pipex_end(int **pipes, int *pids, int processes)
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
	free(pids);
	free_split((void **)pipes);
}