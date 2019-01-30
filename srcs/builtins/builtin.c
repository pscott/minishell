/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:02:44 by pscott            #+#    #+#             */
/*   Updated: 2019/01/30 17:52:46 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	builtin function always free cmd_argv
**			return 0 in case of success
**			return 1 in case of failure
** 
*/

int		handle_builtin(char **cmd_argv, char ***env)
{
	if (!cmd_argv || !(*cmd_argv))
		return (1);
	if (ft_strncmp(cmd_argv[0], "exit", 6) == 0)
		return (mini_exit(cmd_argv, *env));
	if (ft_strncmp(cmd_argv[0], "env", 4) == 0)
		return (mini_env(cmd_argv, *env));
	if (ft_strncmp(cmd_argv[0], "setenv", 7) == 0)
		return (mini_setenv(cmd_argv, env));
	if (ft_strncmp(cmd_argv[0], "unsetenv", 9) == 0)
		return (mini_unsetenv(cmd_argv, *env));
	return (1);
}
