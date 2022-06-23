/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:13 by genouf            #+#    #+#             */
/*   Updated: 2022/06/23 17:11:00 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*		INCLUDE		*/
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "get_next_line.h"
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
void	handle_path(t_data *data, char **env, char **argv);
/*		UTILS			*/
void	print_error(t_data *data, char *reason, int fd, int mode);
void	free_path(t_data *data);
void	free_split(char **str);
int		check_path_access(t_data *data, char *cmd, int *choice, int increment);

#endif