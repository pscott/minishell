/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_only_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:56:18 by pscott            #+#    #+#             */
/*   Updated: 2019/02/11 16:56:57 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	error_noent(char *cmd, char *str)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	error_not_set(char *key)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(" not set\n", 2);
}

void	error_exit(char *cmd, char **env)
{
	free_cmd_env(cmd, env);
	ft_putendl("exit");
	exit(1);
}
