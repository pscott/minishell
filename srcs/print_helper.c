/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:36:46 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 21:37:35 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_prompt(void)
{
	write(1, "$> ", 3);
}

void	print_env(char **env)
{
	int i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

void	print_exit(void)
{
	ft_putstr_fd("exit\n", 2);
	exit(0);
}
