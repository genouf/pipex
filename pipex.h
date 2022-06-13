/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:13 by genouf            #+#    #+#             */
/*   Updated: 2022/06/14 00:46:41 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*		INCLUDE		*/
#include <unistd.h>
#include "libft/libft.h"

typedef struct s_data_fd {
	int	stdout;
	int	file1;
	int	file2;
}				t_data_fd;

/*		FIND_PATH		*/
char	*find_path(char **env, char *cmd);
/*		UTILS			*/
void	print_error(char *reason, int fd);

#endif