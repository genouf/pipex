/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:10 by genouf            #+#    #+#             */
/*   Updated: 2022/06/23 17:11:27 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
	free_split((void **)env_p);
	return (tmp);
}

t_exec	init_exec(char **env, char *str)
{
	t_exec	data_e;

	data_e.cmd = ft_split(str, ' ');
	if (access((data_e.cmd)[0], F_OK) != 0)
	{
		if (ft_strncmp((data_e.cmd)[0], "./", 2) != 0)
		{
			data_e.free = 1;
			data_e.path = find_path(env, (data_e.cmd)[0]);
		}
		else
		{
			free_split((void **)data_e.cmd);
			print_error("Error\nThis cmd is not in rep local !\n", 2);
		}
	}
	else
	{
		data_e.free = 0;
		data_e.path = data_e.cmd[0];
	}
	return (data_e);
}
