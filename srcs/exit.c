/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:33:12 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 21:40:16 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

static int		is_num(char *str)
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

int				should_i_exit(char **argv)
{
	int i;

	if (!argv)
		return (0);
	i = 0;
	if (*argv && ft_strcmp(argv[i], "exit") == 0)
	{
		ft_putstr_fd("exit\n", 2);
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
