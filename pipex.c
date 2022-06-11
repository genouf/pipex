/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:10 by genouf            #+#    #+#             */
/*   Updated: 2022/06/11 18:27:19 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*char *test_path(char **str, char *cmd)
{
	char	*tmp;
	int		i;
	
	i = 0;
	while (str[i])
	{
		
	}
}*/

int	main(int argc, char **argv, char **env)
{
	int	i;
	char	**str;
	char	*tmp;

	(void)argc;
	(void)argv;
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH", 4) == 0)
		{
			str = ft_split(env[i], ':');
			str[0] = ft_strtrim(str[0], "PATH=");
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		tmp = str[i];
		str[i] = ft_strjoin(str[i], "/");
		free(tmp);
		ft_printf("%s\n", str[i]);
		i++;
	}
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (0);
}
