/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:33:59 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 21:34:45 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cmd_in_path(char *cmd, char *env_path)
{
	char	**paths;
	char	*possible_path;
	int		i;

	paths = ft_strsplit(env_path, ':');
	i = 0;
	while (paths[i])
	{
		possible_path = append_path(paths[i], cmd);
		if (access(possible_path, F_OK) == 0)
		{
			if (access(possible_path, X_OK) == 0)
			{
				ft_memdel((void*)&cmd);
				return (possible_path);
			}
			else
				error_exec(cmd);
		}
		i++;
	}
	error_cmd_not_found(cmd);
	return (NULL);
}

static char	*get_cmd_path(char *cmd, char **env)
{
	int i;

	if (!env)
		return (cmd);
	if (*cmd == '/')
		return (cmd);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			return (cmd_in_path(cmd, env[i]));
		}
		i++;
	}
	return (cmd);
}

void		parse_cmd(char *cmd, char **env)
{
	char	**argv;
	int		i;
	pid_t	child_pid;

	if (!cmd || *cmd == 0)
		return ;
	argv = ft_strsplit(cmd, ' ');
	if (should_i_exit(argv) == -1)
		return ;
	i = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		if (!(argv[0] = get_cmd_path(argv[0], env)))
			exit(-1);
		execve(argv[0], argv, env);
		ERR_NOENT(*argv);
	}
	else if (child_pid == -1)
		ERR_FORK;
	else
		wait(&child_pid);
	free_strarray(argv);
}
