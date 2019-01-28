/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:33:12 by pscott            #+#    #+#             */
/*   Updated: 2019/01/28 15:41:39 by pscott           ###   ########.fr       */
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

void			clean_exit(char **cmd_argv, int ext_value)
{
	free_strarray(cmd_argv);
	exit(ext_value);
}

int				should_i_exit(char **cmd_argv)
{
	int i;

	if (!cmd_argv)
		return (0);
	i = 0;
	if (*cmd_argv && ft_strcmp(cmd_argv[i], "exit") == 0)
	{
		ft_putstr_fd("exit\n", 2);
		if (cmd_argv[++i])
		{
			if (is_num(cmd_argv[i]))
			{
				if (cmd_argv[i + 1])
				{
					free_strarray(cmd_argv);
					return (error_arguments());
				}
				exit(ft_atoi(cmd_argv[i]));
			}
			else
				error_numeric(cmd_argv[i]);
		}
		exit(0);
	}
	return (0);
}
