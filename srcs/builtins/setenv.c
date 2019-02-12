/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:30:18 by pscott            #+#    #+#             */
/*   Updated: 2019/02/12 18:38:57 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_envs(char **argv, char **env)
{
	unsigned int	i;

	i = 0;
	while ((is_env_setting(argv[++i])))
	{
		if (setting_is_in_env(argv[i], env) == 0)
			append_new_env(argv[i], env);
		else
			modify_existing_env(argv[i], env);
	}
}

int		mini_setenv(char **argv, char ***env)
{
	char			**new_env;
	unsigned int	settings;
	unsigned int	i;

	settings = 0;
	new_env = parse_env(argv, *env, &settings);
	i = 0;
	free_strarray(*env);
	*env = new_env;
	add_envs((argv), *env);
	free_strarray(argv);
	return (0);
}
