/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:02:24 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 18:10:22 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_env(char *cmd, char **env)
{
	ft_memdel((void*)&cmd);
	free_strarray(env);
}

void	free_strarray(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		ft_memdel((void*)&argv[i]);
		i++;
	}
	ft_memdel((void*)&argv);
}

void	free_argv_env(char **cmd_argv, char **env)
{
	free_strarray(cmd_argv);
	free_strarray(env);
}
