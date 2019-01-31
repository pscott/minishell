/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:50:16 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 18:04:16 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env_setting(char *str)
{
	if (!str)
		return (0);
	str++;
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

int		setting_is_in_env(char *str, char **env)
{
	unsigned int	i;
	unsigned int	var_len;

	if (!str)
		return (0);
	i = -1;
	var_len = get_var_len(str);
	while (env[++i])
	{
		if (ft_strncmp(str, env[i], var_len) == 0)
			return (1);
	}
	return (0);
}

void	modify_existing_env(char *str, char **env)
{
	unsigned int	i;
	unsigned int	var_len;
	char			*tmp;

	i = -1;
	var_len = get_var_len(str);
	while (env[++i])
	{
		if (ft_strncmp(str, env[i], var_len) == 0)
		{
			tmp = env[i];
			env[i] = ft_strdup(str);
			ft_memdel((void*)&tmp);
		}
	}
}

char	*get_corresponding_env_setting(char *key, char **env,
		unsigned int start)
{
	unsigned int	i;
	unsigned int	key_len;
	char			*res;

	i = -1;
	key_len = ft_strlen(&key[start]);
	while (env[++i])
	{
		if (ft_strncmp(env[i], &key[start], key_len) == 0
				&& env[i][key_len] == '=')
		{
			res = ft_strdup(&env[i][key_len + !start + start]);
			ft_memdel((void*)&key);
			return (res);
		}
	}
	ft_memdel((void*)&key);
	return (ft_strdup(""));
}
