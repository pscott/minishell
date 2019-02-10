/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:02:53 by pscott            #+#    #+#             */
/*   Updated: 2019/02/01 11:00:12 by pscott           ###   ########.fr       */
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

char	*get_dollar(char *arg, int *doll_len)
{
	int	i;
	char *res;

	i = 0;
	while (arg[i] && arg[i] != '/')
		i++;
	if (!(res = ft_strnew(i)))
		ERR_MEM;
	res = ft_strncpy(res, arg, i);
	res[i] = 0;
	*doll_len = i + 1;
	return (res);
}

char	*replace_dollar(char *arg, char **env, int dollar_start)
{
	char	*res;
	char	*expand;
	char	*path;
	int		doll_len;

	doll_len = 0;
	path = get_dollar(&arg[dollar_start + 1], &doll_len);
	expand = get_corresponding_env_setting(path, env, 0);
	if (!*expand)
		return (arg);
	if (!(res = ft_strnew(dollar_start + ft_strlen(expand)
					+ ft_strlen(&arg[dollar_start]))))
		ERR_MEM;
	ft_strncpy(res, arg, dollar_start);
	ft_strncat(res, expand, ft_strlen(expand));
	ft_strcat(res, &arg[dollar_start + doll_len]);
	ft_memdel((void*)&expand);
	ft_memdel((void*)&arg);
	return (res);
}

char	*replace_tild(char *token, char **env)
{
	char *res;
	char *tmp;

	res = get_corresponding_env_setting(ft_strdup("HOME"), env, 0);
	tmp = res;
	res = ft_strjoin(res, &token[1]);
	ft_memdel((void*)&tmp);
	if (!*res)
		error_not_set("HOME");
	ft_memdel((void*)&token);
	return (res);
}
