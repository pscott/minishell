/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:57:03 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 20:19:02 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_ac(char **argv)
{
	int i;

	if (!argv || !*argv)
		return (0);
	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int			mini_echo(char **argv)
{
	int i;
	int	ac;

	i = 1;
	ac = get_ac(&argv[1]);
	if (ac == 0)
	{
		ft_putendl("");
		return (0);
	}
	else if (ac && ft_strcmp(argv[1], "-") == 0)
	{
		ft_putstr("");
		i++;
	}
	while (argv[i])
	{
		ft_putstr(argv[i]);
		write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	free_strarray(argv);
	return (0);
}
