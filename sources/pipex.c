/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:51:56 by genouf            #+#    #+#             */
/*   Updated: 2022/06/12 18:21:17 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pfd[2];
	int		pid;
	char	*path;
	char 	**args;

	(void)argc;
	if (pipe(pfd) == -1)
	{
		ft_printf("pipe failed\n");
		return (1);
	}
	if ((pid = fork()) < 0)
	{
		ft_printf("fork failed\n");
		return (2);
	}
	if (pid == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		args = ft_split(argv[3], ' ');
		path = find_path(env, args[0]);
		execve(path, args, env);
		free(path);
		free(args);
		ft_printf(("ls failed"));
		return (3);		
	}
	else
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		args = ft_split(argv[1], ' ');
		path = find_path(env, args[0]);
		execve(path, args, env);
		free(path);
		free(args);
		ft_printf("wc failed");
		return (4);
	}
	return (0);
}
