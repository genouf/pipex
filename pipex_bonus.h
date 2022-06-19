/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:13 by genouf            #+#    #+#             */
/*   Updated: 2022/06/19 16:05:24 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*		INCLUDE		*/
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_exec {
	int		free;
	char	*path;
	char	**cmd;
}				t_exec;

typedef struct s_data_fd {
	int		file1;
	int		file2;
}				t_data_fd;

/*		FIND_PATH		*/
t_exec	init_exec(char **env, char *str);
/*		UTILS			*/
void	print_error(char *reason, int fd);
void	free_split(void **str);
void	free_exec(t_exec data_e);
void	print_split(char **str);
char	*find_path(char **env, char *cmd);
void	free_malloc_failed(void **str, int i);
/*		PIPEX_TOOLS		*/
void	init_pipes(int	***pipes, int processes);
void	close_pipes_child(int ***pipes, int processes, int i);
void	pipex_end(int **pipes, int *pids, int processes);

#endif