/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:33:12 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 17:43:43 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_num(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void			clean_exit(char **cmd_argv, char **env, int ext_value)
{
	free_argv_env(cmd_argv, env);
	exit(ext_value);
}

int				mini_exit(char **cmd_argv, char **env)
{
	int i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (cmd_argv[++i])
	{
		if (is_num(cmd_argv[i]))
		{
			if (cmd_argv[i + 1])
			{
				free_strarray(cmd_argv);
				error_arguments();
				return (0);
			}
			clean_exit(cmd_argv, env, ft_atoi(cmd_argv[i]));
		}
		else
			error_numeric(cmd_argv[i]);
	}
	clean_exit(cmd_argv, env, 0);
	return (1);
}
