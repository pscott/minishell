/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 12:17:02 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 12:44:33 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		mini_cd(char **cmd_argv, char **env)
{
	(void)env;
	if (access(cmd_argv[1], F_OK) == 0)
	{
		if (access(cmd_argv[1], X_OK) != 0)
		{
			ft_printf("{%s}, [%s]\n", cmd_argv[0], cmd_argv[1]);
			error_permi(cmd_argv[0], cmd_argv[1]);
			free_strarray(cmd_argv);
			return (0);
		}
		chdir(cmd_argv[1]);
	}
	else
		ERR_NOENT(cmd_argv[0], cmd_argv[1]);
	return (0);
}
