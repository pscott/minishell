/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:33:12 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 18:42:04 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int		is_num(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int		error_arguments(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}

void	error_numeric(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(-1);
}

int		should_i_exit(char **argv)
{
	int i;

	if (!argv)
		return (0);
	i = 0;
	if (*argv && ft_strcmp(argv[i], "exit") == 0)
	{
		ft_putstr_fd(argv[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
		if (argv[i])
		{
			if (is_num(argv[i]))
			{
				if (argv[i + 1])
					return (error_arguments());
				exit(ft_atoi(argv[i]));
			}
			if (!is_num(argv[i]))
				error_numeric(argv[i]);
		}
		exit(0);
	}
	return (0);
}
