/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 19:38:53 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 13:07:45 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_env_setting(char *str)
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

unsigned int	get_var_len(char *str)
{
	char *begin;

	if (!str)
		return (0);
	begin = str;
	while (*str != '=')
		str++;
	return (str - begin);
}

int				setting_is_in_env(char *str, char **env)
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

unsigned int	how_many_new_env_var(char **argv, char **env,
		unsigned int *settings)
{
	unsigned int	ret;
	unsigned int	i;

	i = 0;
	ret = 0;
	while ((is_env_setting(argv[++i])))
	{
		if (setting_is_in_env(argv[i], env) == 0)
			ret++;
		(*settings)++;
	}
	i = 0;
	while (env[i])
		i++;
	ret += i;
	return (ret);
}

void	append_new_env(char *str, char **env)
{
	unsigned int i;

	i = 0;
	while (env[i])
		i++;
	env[i] = ft_strdup(str);
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

void	execute_command(char *possible_path, char **argv, char **env)
{
	pid_t	child_pid;

	if (*possible_path)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			execve(possible_path, argv, env);
			free_argv_env(argv, env);
			ERR_NOENT("./minishell", possible_path);
		}
		else if (child_pid < 0)
			ERR_FORK;
		else
			wait(&child_pid);
	}
}

char	**parse_env(char **argv, char **env, unsigned int *settings)
{
	char			**new_env;
	unsigned int	new_env_size;
	unsigned int	j;

	new_env_size = how_many_new_env_var(argv, env, settings);
	if (!(new_env = (char **)malloc(sizeof(*new_env) * (new_env_size + 1))))
		ERR_MEM;
	new_env[new_env_size] = NULL;
	j = -1;
	while (env[++j])
		new_env[j] = ft_strdup(env[j]);
	while (j < new_env_size)
	{
		new_env[j] = NULL;
		j++;
	}
	add_envs(argv, new_env);
	return (new_env);
}

int		mini_env(char **argv, char **env)
{
	char			**new_env;
	char			possible_path[PATH_MAX];
	unsigned int	settings;

	settings = 0;
	new_env = parse_env(argv, env, &settings);
	get_path(argv[settings + 1], env, possible_path);
	if (!*(argv + settings + 1))
		print_env(new_env);
	else
		execute_command(possible_path, &(argv[settings + 1]), new_env);
	free_argv_env(argv, new_env);
	return (0);
}
