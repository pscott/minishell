/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_w_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:55:38 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 17:58:36 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

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
	exit(-1);
}

void	error_argv(char **argv)
{
	(void)argv;
	ft_putstr_fd("minishell: my minishell does not support argvs\n", 2);
	exit(1);
}

void	error_read(void)
{
	ft_putstr_fd("Error: failed to read stdin\n", 2);
	exit(1);
}
