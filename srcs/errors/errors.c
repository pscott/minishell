/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 12:47:17 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 18:35:46 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int		error_fork(void)
{
	ft_putstr_fd("Error: could no fork.\n", 2);
	exit(1);
}

char	*error_mem(void)
{
	ft_putstr_fd("Error: failed to allocate memory.\n", 2);
	exit(1);
	return (NULL);
}

int		error_read(void)
{
	ft_putstr_fd("Error: failed to read.\n", 2);
	exit(1);
}

void	error_execve(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(1);
}
