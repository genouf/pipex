/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:46 by genouf            #+#    #+#             */
/*   Updated: 2022/06/23 22:54:09 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char *str_query(char *limiter)
{
	char *result;
	char *tmp;
	char *tmp2;
	
	result = 0;
	limiter = ft_strjoin(limiter, "\n");
	ft_printf("heredoc> ");
	tmp = get_next_line(0);
	while (ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
	{
		tmp2 = result;
		result = ft_strjoin(result, tmp);
		ft_printf("resultin:%s", result);
		free(tmp2);
		free(tmp);
		ft_printf("heredoc> ");
		tmp = get_next_line(0);
	}
	free(limiter);
	free(tmp);
	return (result);
}

void	heredoc(char *limiter, char **env, char **argv)
{
	int 	pipes[2][2];
	int 	pids;
	char 	*entry;
	t_exec	data_e;

	entry = str_query(limiter);
	write(pipes[0][1], entry, ft_strlen(entry));
	free(entry);
	pids = fork();
	if (pids == -1)
		print_error("Error\nFork failed !\n", 2);
	if (pids == 0)
	{
		data_e = init_exec(env, argv[3]);
		dup2(pipes[0][0], STDIN_FILENO);
		dup2(pipes[1][1], STDOUT_FILENO);
		close(pipes[0][0]);
		close(pipes[1][1]);
		close(pipes[0][1]);
		close(pipes[1][0]);
		execve(data_e.path, data_e.cmd, env);
		free_exec(data_e);
		print_error("Error\nCommand Exec failed !\n", 2);		
	}
	p
	dup2(pipes[1][0], STDIN_FILENO);
	dup2()
}