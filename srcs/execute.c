/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:52:59 by pscott            #+#    #+#             */
/*   Updated: 2019/02/12 18:10:20 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_stat(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("failed to use stat(2)\n", 2);
	return (0);
}

static int	error_is_dir(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": is a directory\n", 2);
	return (0);
}

static int	check_file(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (error_stat(path));
	if (S_ISDIR(buf.st_mode))
		return (error_is_dir(path));
	return (1);
}

void		execute_command(char *path, char **argv, char **env)
{
	pid_t		child_pid;

	if (*path)
	{
		if (check_file(path))
		{
			child_pid = fork();
			if (child_pid == 0)
			{
				execve(path, argv, env);
				ERR_NOENT("hey", path);
				exit(-1);
			}
			else if (child_pid < 0)
				ERR_FORK;
			else
				wait(&child_pid);
		}
	}
}
