/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:01:58 by pscott            #+#    #+#             */
/*   Updated: 2019/01/30 18:19:26 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_new_env(char *str, char **env)
{
	unsigned int i;

	i = 0;
	while (env[i])
		i++;
	env[i] = ft_strdup(str);
}

int		valid_unset(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '=')
			return (0);
		str++;
	}
	return (1);
}

void	pop_env(char **env, unsigned int j)
{
	unsigned int	i;

	i = 0;
	ft_memdel((void*)&env[j]);
	while (env[j])
	{
		env[j] = env[j + 1];
		j++;
	}
}

void	delete_envs(char **argv, char **env)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	if (valid_unset(argv[++i]))
	{
		j = 0;
		while (env[j])
		{
			if (ft_strncmp(argv[i], env[j], ft_strlen(argv[i])) == 0)
				pop_env(env, j);
			j++;
		}
	}
}

int		mini_unsetenv(char **argv, char **env)
{
	delete_envs(&argv[1], env);
	free_strarray(argv);
	return (0);
}
