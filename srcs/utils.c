/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:18:02 by pscott            #+#    #+#             */
/*   Updated: 2019/01/28 20:34:12 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_path(char *possible_path, char *origin, char *append)
{
	int		origin_len;
	int		append_len;

	if (!append)
		ft_strcpy(possible_path, origin);
	else if (!origin)
		ft_strcpy(possible_path, append);
	else
	{
		origin_len = ft_strlen(origin);
		append_len = ft_strlen(append);
		ft_strncpy(possible_path, origin, origin_len + 1);
		possible_path[origin_len] = '/';
		ft_strncpy(possible_path + origin_len + 1, append, append_len + 1);
	}
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

int		slash_in_cmd(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

void	free_argv_env(char **cmd_argv, char **env)
{
	free_strarray(cmd_argv);
	free_strarray(env);
}
