/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:24:33 by pscott            #+#    #+#             */
/*   Updated: 2019/01/29 13:10:29 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access(char *possible_path)
{
	if (access(possible_path, F_OK) == 0)
	{
		if (access(possible_path, X_OK) != 0)
			error_exec(possible_path);
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

static void	get_path(char *cmd, char **env, char *possible_path)
{
	int i;
	int	cmd_len;

	cmd_len = ft_strlen(cmd);
	if (!env || !(*env) || slash_in_cmd(cmd))
	{
		ft_strncpy(possible_path, cmd, cmd_len + 1);
		if (!check_access(possible_path))
		{
			ERR_NOENT(possible_path);
			*possible_path = 0;
		}
		return ;
	}
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			cmd_in_path(cmd, env[i], possible_path);
			return ;
		}
		i++;
	}
	ft_strncpy(possible_path, cmd, cmd_len + 1);
}

void		handle_cmd(char **cmd_argv, char **env)
{
	char	possible_path[PATH_MAX];
	pid_t	child_pid;

	if (handle_builtin(cmd_argv, env) == 0)
		return ;
	get_path(cmd_argv[0], env, possible_path);
	if (*possible_path)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			if (*possible_path == 0)
				clean_exit(cmd_argv, env, -1);
			execve(possible_path, cmd_argv, env);
			free_argv_env(cmd_argv, env);
			ERR_NOENT(possible_path);
		}
		else if (child_pid < 0)
			ERR_FORK;
		else
			wait(&child_pid);
	}
	free_argv_env(cmd_argv, env);
}
