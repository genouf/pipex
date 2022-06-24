/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:51:56 by genouf            #+#    #+#             */
/*   Updated: 2022/06/24 16:49:33 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_data_fd(t_data_fd *data, char **argv, int argc)
{
	if (access(argv[1], F_OK) != 0)
		print_error("Error\nThe path of file1 is wrong !\n", 2);
	if (access(argv[1], R_OK) != 0)
		print_error("Error\nIncorrect access to file1 !\n", 2);
	if (access(argv[1], R_OK | F_OK) == 0)
	{
		data->file1 = open(argv[1], O_RDONLY, 0500);
		if (data->file1 == -1)
			print_error("Error\nBad file descriptor !\n", 2);
	}
	if (access(argv[argc - 1], F_OK) != 0)
	{
		data->file2 = open(argv[argc - 1], O_CREAT | O_WRONLY, 0664);
		if (data->file2 == -1)
			print_error("Error\nBad file descriptor !\n", 2);
	}
	else
	{
		if (access(argv[argc - 1], W_OK) != 0)
			print_error("Error\nIncorrect access to file2 !\n", 2);
		data->file2 = open(argv[argc - 1], O_TRUNC | O_WRONLY, 0664);
		if (data->file2 == -1)
			print_error("Error\nBad file descriptor !\n", 2);
	}
}

void	init_pipex_data(int processes, int ***pipes, int **pids)
{
	int	i;

	*pids = (int *)malloc(sizeof(int) * processes);
	if (*pids == NULL)
		print_error("Error\nMalloc failed !\n", 2);
	*pipes = (int **)malloc(sizeof(int *) * (processes + 1));
	if (*pipes == NULL)
	{
		free(*pids);
		print_error("Error\nMalloc failed !\n", 2);
	}
	i = 0;
	while (i < processes)
	{
		(*pipes)[i] = (int *)malloc(sizeof(int) * 2);
		if ((*pipes)[i] == NULL)
		{
			free_malloc_failed((void **)*pipes, i - 1);
			free(*pids);
			print_error("Error\nMalloc failed !\n", 2);
		}
		i++;
	}
	(*pipes)[i] = 0;
}

void	process_dup(t_data_fd data, int **pipes, int i, int processes)
{
	int	check1;
	int	check2;

	if (i == 0)
		check1 = dup2(data.file1, STDIN_FILENO);
	else
		check1 = dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i == processes - 1)
		check2 = dup2(data.file2, STDOUT_FILENO);
	else
		check2 = dup2(pipes[i][1], STDOUT_FILENO);
	if (check1 == -1 || check2 == -1)
		print_error("Error\nDup failed !\n", 2);
	if (i != 0)
		check1 = close(pipes[i - 1][0]);
	if (i != processes - 1)
		check1 = close(pipes[i][1]);
	if (check1 == -1)
		print_error("Error\nPipe close failed !\n", 2);
	check1 = close(data.file1);
	check1 = close(data.file2);
	if (check1 == -1 || check2 == -1)
		print_error("Error\nClose failed !\n", 2);
}

int	pipex(t_data_pip *data, char **env, int processes, char **argv)
{
	int		i;

	init_pipex_data(processes, &data->pipes, &data->pids);
	init_pipes(&data->pipes, processes, data);
	i = -1;
	while (++i < processes)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			print_error_free("Error\nFork failed !\n", 2, data);
		data->data_e = init_exec(env, argv[i + 2]);
		if (data->pids[i] == 0)
		{
			close_pipes_child(&data->pipes, processes, i);
			process_dup(data->data_fd, data->pipes, i, processes);
			free_pp(data->pipes, data->pids);
			execve(data->data_e.path, data->data_e.cmd, env);
			free_exec(data->data_e);
			print_error("Error\nCommand Exec failed !\n", 2);
		}
		free_exec(data->data_e);
	}
	pipex_end(data->pipes, data->pids, processes, data);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data_pip	data;

	if (argc > 4)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			heredoc(argv[2], env, argv, argc);
			exit(1);
		}
		init_data_fd(&data.data_fd, argv, argc);
		pipex(&data, env, argc - 3, argv);
	}
	else
	{
		ft_putstr_fd("Error\nWrong number of arguments !\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}
