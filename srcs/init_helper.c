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

void	increm_shlvl(char **env)
{
	unsigned int	i;
	char			*new_shlvl;
	char			*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("SHLVL=", env[i], 5) == 0)
		{
			tmp = ft_itoa(ft_atoi(&env[i][6]) + 1);
			new_shlvl = ft_strjoin("SHLVL=", tmp);
			ft_memdel((void*)&tmp);
			tmp = env[i];
			env[i] = new_shlvl;
			ft_memdel((void*)&tmp);
			return ;
		}
		i++;
	}
	ft_putstr_fd("Error: SHLVL not found\n", 2);
}

char	**cpy_2d_strarray(char **env)
{
	int		i;
	char	**res;

	if (!env || !*env)
		return (empty_env());
	i = 0;
	while (env[i])
		i++;
	if (!(res = (char**)MALLOC(sizeof(*res) * (i + 1))))
		ERR_MEM;
	res[i] = NULL;
	i = -1;
	while (env[++i])
		res[i] = ft_strdup(env[i]);
	increm_shlvl(res);
	return (res);
}

char	*replace_dollar(char *token, char **env, int dollar_start)
{
	char *res;
	char *tmp;

	res = get_corresponding_env_setting(token, env, 0);
	tmp = res;
	res = ft_strjoin(res, &token[1]);
	ft_memdel((void*)&tmp);
	if (!*res)
		error_not_set("HOME");
	ft_memdel((void*)&token);
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
