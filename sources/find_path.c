/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:10 by genouf            #+#    #+#             */
/*   Updated: 2022/06/15 18:55:44 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	*test_path(char **str, char *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (str[i])
	{
		path = ft_strjoin(str[i], cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static void	add_slash(char ***str)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i])
	{
		tmp = (*str)[i];
		(*str)[i] = ft_strjoin((*str)[i], "/");
		free(tmp);
		i++;
	}
}

char	*find_path(char **env, char *cmd)
{
	int		i;
	char	**env_p;
	char	*tmp;

	i = 0;
	if (env[0] == NULL)
		return (NULL);
	while (env[i])
	{
		if (strncmp(env[i], "PATH", 4) == 0)
		{
			env_p = ft_split(env[i], ':');
			tmp = env_p[0];
			env_p[0] = ft_strtrim(env_p[0], "PATH=");
			free(tmp);
		}
		i++;
	}
	add_slash(&env_p);
	tmp = test_path(env_p, cmd);
	free_split(env_p);
	return (tmp);
}

void	init_cmd_path(t_data *data, char **env, char **argv, int choice)
{
	if (choice == 1 || choice == 3)
	{
		data->path1 = find_path(env, data->cmd1[0]);
		if (data->path1 == NULL)
		{
			free_split(data->cmd1);
			free_split(data->cmd2);
			print_error(data, "Error\nBad command1 !\n", 1, 0);
		}
	}
	if (choice == 2 || choice == 3)
	{
		data->path2 = find_path(env, data->cmd2[0]);
		if (data->path2 == NULL)
		{
			if (choice == 1)
				free(data->path1);
			free_split(data->cmd1);
			free_split(data->cmd2);
			print_error(data, "Error\nBad command2 !\n", 1, 0);
		}
	}
}

void	check_path_access()

void	handle_path(t_data *data, char **env, char **argv)
{
	int choice;

	data->cmd1 = ft_split(argv[2], ' ');
	data->cmd2 = ft_split(argv[3], ' ');
	choice = 0;
	if (access(argv[1], F_OK != 0))
	{
		if (strncmp(argv[1], "./", 2) != 0)
			choice += 1;
		else
			choice -= 1;
	}
	else
		data->path1 = ft_strdup(argv[1]);
	if (access(argv[4], F_OK != 0))
	{
		if (strncmp(argv[1], "./", 2) != 0)
			choice += 2;
		else
			choice -= 2;
	}
	else
		data->path2 = ft_strdup(argv[4]);
	if (choice < 0)
		print_error(data, "Error\nIncorrect path !\n", 1, 0);
	init_cmd_path(data, env, argv, choice);
}