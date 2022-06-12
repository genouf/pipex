/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:10 by genouf            #+#    #+#             */
/*   Updated: 2022/06/12 17:52:05 by genouf           ###   ########.fr       */
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

static void	free_env_p(char **env_p)
{
	int	i;

	i = 0;
	while (env_p[i])
	{
		free(env_p[i]);
		i++;
	}
	free(env_p);
}

char	*find_path(char **env, char *cmd)
{
	int		i;
	char	**env_p;
	char	*tmp;

	i = 0;
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
	free_env_p(env_p);
	return (tmp);
}
