/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:52:59 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 20:22:38 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char *possible_path, char **argv, char **env)
{
	pid_t	child_pid;

	if (*possible_path)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			execve(possible_path, argv, env);
			ERR_NOENT("minishell", possible_path);
			exit(-1);
		}
		else if (child_pid < 0)
			ERR_FORK;
		else
			wait(&child_pid);
	}
}
