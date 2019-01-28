/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:02:44 by pscott            #+#    #+#             */
/*   Updated: 2019/01/28 18:27:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_builtin(char **cmd_argv, char **env)
{
	(void)env;
	if (!cmd_argv || !(*cmd_argv))
		return (1);
	if (ft_strncmp(cmd_argv[0], "exit", 6) == 0)
		return (mini_exit(cmd_argv));
	return (1);
}
