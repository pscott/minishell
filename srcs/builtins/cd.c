/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 12:17:02 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 17:28:40 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	get_key_position(char *key, char **env)
{
	unsigned int	i;
	unsigned int	key_len;

	i = -1;
	key_len = ft_strlen(key);
	while (env[++i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
	}
	return (-1);
}

void	update_pwd(char **env)
{
	char			*tmp;
	char			current[PATH_MAX];
	unsigned int	i;

	if ((i = get_key_position("OLDPWD", env)) > 0)
	{
		tmp = env[i];
		env[i] = ft_strjoin("OLDPWD=", &env[get_key_position("PWD", env)][4]);
		free(tmp);
	}
	else
		error_not_set("OLDPWD");
	if ((i = get_key_position("PWD", env)) > 0)
	{
		tmp = env[i];
		env[i] = ft_strjoin("PWD=", getcwd(current, PATH_MAX));
		free(tmp);
	}
	else
		error_not_set("PWD");
}

char	*check_if_old(char **argv, char **env)
{
	char *res;

	if (*(argv[1]) == '-')
		res = get_corresponding_env_setting(ft_strdup("OLDPWD"), env, 0);
	else
		res = ft_strdup(argv[1]);
	return (res);
}

int		mini_cd(char **cmd_argv, char **env)
{
	char *env_name;

	if (!cmd_argv[1])
		env_name = get_corresponding_env_setting(ft_strdup("HOME"), env, 0);
	else
		env_name = check_if_old(cmd_argv, env);
	if (*env_name == 0)
	{
		if (!cmd_argv[1])
			error_not_set("HOME");
		else
			error_not_set("OLDPWD");
	}
	else if (access(env_name, F_OK) == 0)
	{
		if (access(env_name, X_OK) != 0)
		{
			error_permi(cmd_argv[0], env_name);
			ft_memdel((void*)&env_name);
			free_strarray(cmd_argv);
			return (0);
		}
		chdir(env_name);
		update_pwd(env);
	}
	else
		ERR_NOENT(cmd_argv[0], env_name);
	ft_memdel((void*)&env_name);
	free_strarray(cmd_argv);
	return (0);
}
