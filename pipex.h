/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:09:13 by genouf            #+#    #+#             */
/*   Updated: 2022/06/12 17:52:55 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*		INCLUDE		*/
#include <unistd.h>
#include "libft/libft.h"

/*		FIND_PATH		*/
char	*find_path(char **env, char *cmd);

#endif