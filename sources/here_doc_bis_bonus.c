/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bis_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:03:51 by genouf            #+#    #+#             */
/*   Updated: 2022/06/24 13:04:52 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_heredoc_fd(char **argv, int *fd, int argc)
{
	int	index;

	index = argc - 1;
	if (access(argv[index], F_OK) != 0)
	{
		*fd = open(argv[index], O_CREAT | O_WRONLY, 0664);
		if (*fd == -1)
			print_error("Error\nBad file descriptor !\n", 2);
	}
	else
	{
		if (access(argv[index], W_OK) != 0)
			print_error("Error\nIncorrect access to heredoc file !\n", 2);
		*fd = open(argv[index], O_APPEND | O_WRONLY, 0664);
		if (*fd == -1)
			print_error("Error\nBad file descriptor !\n", 2);
	}
}
