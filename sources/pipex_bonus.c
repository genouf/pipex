/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:51:56 by genouf            #+#    #+#             */
/*   Updated: 2022/06/17 12:34:09 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_data_fd(t_data *data, char **argv)
{
	if (access(argv[1], F_OK) != 0)
		print_error(data, "Error\nThe path of file1 is wrong !\n", 1, 0);
	if (access(argv[1], R_OK) != 0)
		print_error(data, "Error\nIncorrect access to file1 !\n", 1, 0);
	if (access(argv[1], R_OK | F_OK) == 0)
	{
		data->file1 = open(argv[1], O_RDONLY, 0500);
		if (data->file1 == -1)
			print_error(data, "Error\nBad file descriptor !\n", 1, 0);
	}
	if (access(argv[4], F_OK) != 0)
	{
		data->file2 = open(argv[4], O_CREAT | O_WRONLY, 0664);
		if (data->file2 == -1)
			print_error(data, "Error\nBad file descriptor !\n", 1, 0);
	}
	else
	{
		if (access(argv[4], W_OK) != 0)
			print_error(data, "Error\nIncorrect access to file2 !\n", 1, 0);
		data->file2 = open(argv[4], O_TRUNC | O_WRONLY, 0664);
		if (data->file2 == -1)
			print_error(data, "Error\nBad file descriptor !\n", 1, 0);
	}
	data->stdout_fd = dup(1);
}

void	child(t_data *data, int *pfd, char **env)
{
	int	check1;
	int	check2;

	check1 = dup2(data->file1, STDIN_FILENO);
	check2 = dup2(pfd[1], STDOUT_FILENO);
	if (check1 == -1 || check2 == -1)
		print_error(data, "Error\nDup failed !\n", 1, 1);
	check1 = close(pfd[0]);
	check2 = close(pfd[1]);
	if (check1 == -1 || check2 == -1)
		print_error(data, "Error\nPipe close failed !\n", 1, 1);
	execve(data->path1, data->cmd1, env);
	print_error(data, "Error\nCommand1 failed !\n", 1, 1);
}

void	parent(t_data *data, int *pfd, char **env)
{
	int	check1;
	int	check2;

	check1 = dup2(pfd[0], STDIN_FILENO);
	check2 = dup2(data->file2, STDOUT_FILENO);
	if (check1 == -1 || check2 == -1)
		print_error(data, "Error\nDup failed !\n", 1, 1);
	check1 = close(pfd[1]);
	check2 = close(pfd[0]);
	if (check1 == -1 || check2 == -1)
		print_error(data, "Error\nPipe close failed !\n", 1, 1);
	execve(data->path2, data->cmd2, env);
	print_error(data, "Error\nCommand2 failed !\n", 1, 1);
	wait(NULL);
}

void	pipex(t_data *data, char **env, int processes)
{
	int pids[processes];
	int	pipes[processes + 1][2];
	int	i;
	int	j;
	int	x;
	int y;
	int check1;
	int	check2;

	i = 0;
	/* Creation des pipes */
	while (i < processes + 1)
	{
		if (pipe(pipes[i]) == -1)
			print_error(data, "Error\nPipe failed !\n", 1, 1);
		i++;
	}
	/* Creation des processes */
	i = 0;
	while (i < processes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			print_error(data, "Error\nFork failed !\n", 1, 1);
		/* Child process */
		if (pids[i] == 0)
		{
			/* Fermeture des pipes que l'on n'utilise pas */
			j = 0;
			while (j < processes + 1)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
				j++;
			}
			check1 = dup2(pipes[i][0], 0);
			check2 = dup2(pipes[i + 1][1], 1);
			if (check1 == -1 || check2 == -1)
				print_error(data, "Error\nDup failed !\n", 1, 1);
			check1 = close(pipes[i][0]);
			check2 = close(pipes[i + 1][0]);
			if (check1 == -1 || check2 == -1)
				print_error(data, "Error\nPipe close failed !\n", 1, 1);
			execve()
			return (0);
		}
		i++;
	}
	/* Main process */
	y = 5;
	
	/* Wait processes */
	i = -1;
	while (++i < processes)
		wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc < 5)
	{
		//handle_path(&data, env, argv);
		//init_data_fd(&data, argv);
		pipex(&data, env, argc - 3);
	}
	else
	{
		ft_putstr_fd("Error\nWrong number of arguments !\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}
