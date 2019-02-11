/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_w_return.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:59:40 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 17:59:40 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int		error_permi(char *cmd, char *str)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": permission denied\n", 2);
	return (-1);
}

int		error_arguments(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (-1);
}
