/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:35:18 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 17:43:44 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int		error_permi(char *cmd, char *str)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": permission denied\n", 2);
	return (0);
}

int		error_arguments(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (-1);
}

void	error_numeric(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(-1);
}

void	error_no_pwd(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit (-1);
}

void	error_not_set(char *key)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(" not set\n", 2);
}

void	error_argv(char **argv)
{
	(void)argv;
	ft_putstr_fd("minishell: my minishell does not support argvs\n", 2);
	exit(1);
}
