/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:51:56 by genouf            #+#    #+#             */
/*   Updated: 2022/06/17 17:09:09 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	init_data_fd(t_data_fd *data, char **argv)
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
	if (access(argv[4], F_OK) != 0)
	{
		data->file2 = open(argv[4], O_CREAT | O_WRONLY, 0664);
		if (data->file2 == -1)
			print_error("Error\nBad file descriptor !\n", 2);
	}
	else
	{
		if (access(argv[4], W_OK) != 0)
			print_error("Error\nIncorrect access to file2 !\n", 2);
		data->file2 = open(argv[4], O_TRUNC | O_WRONLY, 0664);
		if (data->file2 == -1)
			print_error("Error\nBad file descriptor !\n", 2);
	}
}

int	pipex(t_data_fd data, char **env, int processes, char **argv)
{
	int 	pids[processes];
	int		pipes[processes + 1][2];
	int		i;
	int		j;
	int 	check1;
	int		check2;
	 t_exec	data_e;

	i = 0;
	/* Creation des pipes */
	while (i < processes + 1)
	{
		if (pipe(pipes[i]) == -1)
			print_error("Error\nPipe failed !\n", 2);
		i++;
	}
	check1 = dup2(pipes[0][1], data.file1);
	check2 = dup2(pipes[processes - 1][0], data.file2);
	close(pipes[0][1]);
	close(pipes[processes - 1][0]);
	/* Creation des processes */
	i = 0;
	while (i < processes)
	{
		ft_printf("JE SUIS LAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		pids[i] = fork();
		if (pids[i] == -1)
			print_error("Error\nFork failed !\n", 2);
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
			check1 = dup2(pipes[i][0], STDIN_FILENO);
			check2 = dup2(pipes[i + 1][1], STDOUT_FILENO);
			ft_printf("ALLLLLLLLLLLLLLOOOOO%d\n", check1);
			ft_printf("%d\n", check2);
			if (check1 == -1 || check2 == -1)
				print_error("Error\nDup failed !\n", 2);
			check1 = close(pipes[i][0]);
			check2 = close(pipes[i + 1][1]);
			if (check1 == -1 || check2 == -1)
				print_error("Error\nPipe close failed !\n", 2);
			data_e = init_exec(env, argv[i + 2]);
			ft_printf("%s", data_e.path);
			execve(data_e.path, data_e.cmd, env);
			print_error("Error\nCommand Exec failed !\n", 2);
			return (0);
		}
		//free_exec(data_e);
		i++;
	}
	/* Wait processes */
	i = -1;
	while (++i < processes)
		wait(NULL);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data_fd	data;
	
	if (argc > 4)
	{
		init_data_fd(&data, argv);
		pipex(data, env, argc - 3, argv);
		/*t_exec data_e = init_exec(env, argv[2]);
		ft_printf("%s\n",  data_e.path);*/
	}
	else
	{
		ft_putstr_fd("Error\nWrong number of arguments !\n", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}
