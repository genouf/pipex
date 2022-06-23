/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: genouf <genouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:47:46 by genouf            #+#    #+#             */
/*   Updated: 2022/06/23 18:12:37 by genouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char *str_query(char *limiter)
{
	char *result;
	char *tmp;
	char *tmp2;
	
	result = NULL;
	limiter = ft_strjoin(limiter, "\n");
	ft_printf("heredoc> ");
	tmp = get_next_line(0);
	while (ft_strncmp(tmp, limiter, ft_strlen(limiter)) != 0)
	{
		tmp2 = result;
		result = ft_strjoin(result, tmp);
		ft_printf("resultin:%s", result);
		free(tmp2);
		free(tmp);
		ft_printf("heredoc> ");
		tmp = get_next_line(0);
	}
	free(limiter);
	free(tmp);
	return (result);
}