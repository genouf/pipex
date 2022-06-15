/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:13 by genouf            #+#    #+#             */
/*   Updated: 2022/06/15 10:43:47 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*		INCLUDE		*/
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data {
	int		stdout_fd;
	int		file1;
	int		file2;
	char	*path1;
	char	**cmd1;
	char	*path2;
	char	**cmd2;
}				t_data;

/*		FIND_PATH		*/
char	*find_path(char **env, char *cmd);
/*		UTILS			*/
void	print_error(t_data *data, char *reason, int fd, int mode);
void	free_split(char **str);

#endif