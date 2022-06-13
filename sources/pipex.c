/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:51:56 by genouf            #+#    #+#             */
/*   Updated: 2022/06/14 00:40:40 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	init_data_fd(t_data_fd *data, char *argv)
{
	if (access(argv[1], F_OK) != 0)
	{
		ft_putstr_fd("Error\nThe path of file1 is wrong !\n", 1);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], R_OK) != 0)
	{
		ft_putstr_fd("Error\nYou don't have correct access !\n", 1);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], R_OK | F_OK) == 0)
		data->file1 = open(argv[1], O_RDONLY, )

		
}

int	main(int argc, char **argv, char **env)
{
	t_data_fd	data;

	(void)argv;
	if (argc == 5 && env != NULL)
	{
		
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
