/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:02:53 by pscott            #+#    #+#             */
/*   Updated: 2019/02/11 16:30:59 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_env_len(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**empty_env(void)
{
	char **res;
	char *cwd;

	if (!(res = (char**)MALLOC(sizeof(*res) * (3))))
		ERR_MEM;
	if (!(cwd = getcwd(NULL, PATH_MAX)))
	{
		error_no_pwd("error retrieving current directory: getcwd: cannot"
				"access parent directories: No such file or directory");
	}
	res[0] = ft_strjoin("PWD=", cwd);
	res[1] = ft_strdup("SHLVL=1");
	res[2] = NULL;
	free(cwd);
	return (res);
}

void	append_env(char *token, char *value, char ***env)
{
	char	**res;
	char	**old_env;
	char	*tmp;
	int		len;

	if (token && value)
	{
		old_env = *env;
		len = get_env_len(*env) + 1;
		if (!(res = (char **)MALLOC(sizeof(*res) * (len + 1))))
			ERR_MEM;
		res[len] = NULL;
		len = -1;
		while ((*env)[++len])
			res[len] = ft_strdup((*env)[len]);
		res[len] = ft_strjoin(token, "=");
		tmp = res[len];
		res[len] = ft_strjoin(res[len], value);
		ft_memdel((void*)&tmp);
		*env = res;
		free_strarray(old_env);
	}
}

void	increm_shlvl(char ***env)
{
	unsigned int	i;
	char			*new_shlvl;
	char			*tmp;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp("SHLVL=", (*env)[i], 5) == 0)
		{
			tmp = ft_itoa(ft_atoi(&((*env)[i][6])) + 1);
			new_shlvl = ft_strjoin("SHLVL=", tmp);
			ft_memdel((void*)&tmp);
			tmp = (*env)[i];
			(*env)[i] = new_shlvl;
			ft_memdel((void*)&tmp);
			return ;
		}
		i++;
	}
	append_env("SHLVL", "1", env);
}

char	**cpy_2d_strarray(char **env)
{
	int		i;
	char	**res;

	if (!env || !*env)
		return (empty_env());
	i = get_env_len(env);
	if (!(res = (char**)MALLOC(sizeof(*res) * (i + 1))))
		ERR_MEM;
	res[i] = NULL;
	i = -1;
	while (env[++i])
		res[i] = ft_strdup(env[i]);
	increm_shlvl(&res);
	return (res);
}
