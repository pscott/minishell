/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:24:33 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 20:22:28 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_access(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
			error_permi("minishell", path);
		return (1);
	}
	else
		return (0);
}

static void	cmd_in_path(char *cmd, char *env_path, char *possible_path)
{
	char	**paths;
	int		i;

	paths = ft_strsplit(env_path, ":");
	i = -1;
	while (paths[++i])
	{
		join_path(possible_path, paths[i], cmd);
		if (check_access(possible_path))
		{
			free_strarray(paths);
			return ;
		}
	}
	free_strarray(paths);
	ft_strncpy(possible_path, cmd, ft_strlen(cmd) + 1);
	if (!check_access(possible_path))
	{
		error_cmd_not_found(possible_path);
		*possible_path = 0;
	}
}

void		get_path(char *cmd, char **env, char *possible_path)
{
	int i;

	if (!cmd)
		return ;
	if (!env || !(*env) || slash_in_cmd(cmd))
	{
		ft_strncpy(possible_path, cmd, ft_strlen(cmd) + 1);
		if (!check_access(possible_path))
		{
			ERR_NOENT("minishell", possible_path);
			*possible_path = 0;
		}
		return ;
	}
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			cmd_in_path(cmd, env[i], possible_path);
			return ;
		}
	}
	ft_strncpy(possible_path, cmd, ft_strlen(cmd) + 1);
}

void		handle_cmd(char **cmd_argv, char ***env)
{
	char	possible_path[PATH_MAX];

	*possible_path = 0;
	if (handle_builtin(cmd_argv, env) == 0)
		return ;
	get_path(cmd_argv[0], *env, possible_path);
	execute_command(possible_path, cmd_argv, *env);
	free_strarray(cmd_argv);
}
