/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:46 by genouf            #+#    #+#             */
/*   Updated: 2022/06/24 13:04:10 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*str_query(char *limiter)
{
	char	*result;
	char	*tmp;
	char	*tmp2;

	result = 0;
	limiter = ft_strjoin(limiter, "\n");
	ft_printf("heredoc> ");
	tmp = get_next_line(0);
	while (ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
	{
		tmp2 = result;
		result = ft_strjoin(result, tmp);
		free(tmp2);
		free(tmp);
		ft_printf("heredoc> ");
		tmp = get_next_line(0);
	}
	free(limiter);
	free(tmp);
	return (result);
}

void	process_child(int pipes[2][2])
{
	int	check1;
	int	check2;

	check1 = dup2(pipes[0][0], STDIN_FILENO);
	check2 = dup2(pipes[1][1], STDOUT_FILENO);
	if (check1 == -1 || check2 == -1)
		print_error("Error\nDup failed !\n", 2);
	check1 = close(pipes[0][0]);
	check2 = close(pipes[1][1]);
	if (check1 == -1 || check2 == -1)
		print_error("Error\nClose failed !\n", 2);
	check1 = close(pipes[0][1]);
	check2 = close(pipes[1][0]);
	if (check1 == -1 || check2 == -1)
		print_error("Error\nClose failed !\n", 2);
}

void	process_parent(int pipes[2][2], int fd)
{
	int	check1;
	int	check2;

	check1 = dup2(pipes[1][0], STDIN_FILENO);
	check2 = dup2(fd, STDOUT_FILENO);
	if (check1 == -1 || check2 == -1)
		print_error("Error\nDup failed !\n", 2);
	check1 = close(pipes[0][0]);
	check2 = close(pipes[1][1]);
	if (check1 == -1 || check2 == -1)
		print_error("Error\nClose failed !\n", 2);
	check1 = close(pipes[0][1]);
	check2 = close(pipes[1][0]);
	if (check1 == -1 || check2 == -1)
		print_error("Error\nClose failed !\n", 2);
}

void	init_heredoc(char **argv, int argc, t_heredoc *doc, char *limiter)
{
	char	*entry;

	init_heredoc_fd(argv, &doc->fd, argc);
	if (pipe(doc->pipes[0]) == -1 || pipe(doc->pipes[1]) == -1)
		print_error("Error\nPipe failed !\n", 2);
	entry = str_query(limiter);
	write(doc->pipes[0][1], entry, ft_strlen(entry));
	free(entry);
}

int	heredoc(char *limiter, char **env, char **argv, int argc)
{
	t_heredoc	doc;

	init_heredoc(argv, argc, &doc, limiter);
	doc.pids = fork();
	if (doc.pids == -1)
		print_error("Error\nFork failed !\n", 2);
	if (doc.pids == 0)
	{
		process_child(doc.pipes);
		doc.data_e = init_exec(env, argv[3]);
		execve(doc.data_e.path, doc.data_e.cmd, env);
		free_exec(doc.data_e);
		print_error("Error\nCommand Exec failed !\n", 2);
	}
	process_parent(doc.pipes, doc.fd);
	doc.data_e = init_exec(env, argv[4]);
	execve(doc.data_e.path, doc.data_e.cmd, env);
	free_exec(doc.data_e);
	print_error("Error\nCommand Exec failed !\n", 2);
	wait(NULL);
	return (0);
}
