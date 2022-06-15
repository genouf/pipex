/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:51:56 by genouf            #+#    #+#             */
/*   Updated: 2022/06/15 10:59:14 by genouf           ###   ########.fr       */
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
		data->file2 = open(argv[4], O_CREAT | O_WRONLY, 0644);
		if (data->file2 == -1)
			print_error(data, "Error\nBad file descriptor !\n", 1, 0);
	}
	else
	{
		if (access(argv[4], W_OK) != 0)
			print_error(data, "Error\nIncorrect access to file2 !\n", 1, 0);
		data->file2 = open(argv[4], O_TRUNC | O_WRONLY, 0644);
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

void	pipex(t_data *data, char **env)
{
	int	pid;
	int	pfd[2];

	if (pipe(pfd) == -1)
		print_error(data, "Error\nPipe failed !\n", 1, 1);
	pid = fork();
	if (pid < 0)
		print_error(data, "Error\nFork failed !\n", 1, 1);
	if (pid == 0)
		child(data, pfd, env);
	else
		parent(data, pfd, env);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc == 5 && env != NULL)
	{
		init_data_fd(&data, argv);
		init_cmd_path(&data, env, argv);
		pipex(&data, env);
	}
	else
	{
		if (env == NULL)
		{
			ft_putstr_fd("Error\nEnvironment error !\n", 1);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_putstr_fd("Error\nWrong number of arguments !\n", 1);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
