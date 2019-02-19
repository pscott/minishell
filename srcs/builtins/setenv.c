/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:30:18 by pscott            #+#    #+#             */
/*   Updated: 2019/02/19 11:55:08 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_setenv(char *arg, char **env)
{
	int		i;
	char	*start;
	char	*tmp;
	char	*res;

	i = 0;
	start = ft_strchr(arg, '=');
	if (start && start[1] == '~')
	{
		tmp = get_corresponding_env_setting(ft_strdup("HOME"), env, 0);
		if (!(res = ft_strnew(ft_strlen(arg) - 1 + ft_strlen(tmp))))
			ERR_MEM;
		ft_strncpy(res, arg, start - arg + 1);
		ft_strncpy(res + (start - arg + 1), tmp, ft_strlen(tmp));
		ft_strncpy(res + (start - arg + 1) + ft_strlen(tmp), arg + (start - arg)
				+ 2, ft_strlen(start) - 1);
		ft_memdel((void*)&arg);
		ft_memdel((void*)&tmp);
		return (res);
	}
	return (arg);
}

void	add_envs(char **argv, char **env)
{
	unsigned int	i;

	i = 0;
	while ((is_env_setting(argv[++i])))
	{
		argv[i] = expand_setenv(argv[i], env);
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
