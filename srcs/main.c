/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:43:53 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 17:41:01 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_env(char *cmd, char **env)
{
	ft_memdel((void*)&cmd);
	free_strarray(env);
}

char	**empty_env(void)
{
	char **res;
	char *cwd;

	if (!(res = (char**)MALLOC(sizeof(*res) * (3))))
		ERR_MEM;
	if (!(cwd = getcwd(NULL, PATH_MAX)))
	{
		error_no_pwd("error retrieving currentin directory: getcwd: cannot"
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

void	read_stdin(char **cmd, char **env)
{
	int		ret;
	char	buf;
	int		i;
	size_t	mall_size;

	(void)env;
	mall_size = INIT_MALL_SIZE;
	i = 0;
	buf = 0;
	while ((ret = read(0, &buf, 1) > 0) && buf != '\n')
	{
		*cmd = ft_realloc((void*)*cmd, ft_strlen(*cmd), &mall_size, ret);
		ft_strncat((*cmd + i++), &buf, 1);
	}
	if (buf == '\n')
		return ;
	else if (ret == 0)
	{
		ft_putstr_fd("exit\n", 2);
		free_cmd_env(*cmd, env);
		exit(0);
	}
	else if (ret < 0)
		ERR_READ;
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
		if (ft_strncmp(env[i], &key[start], key_len) == 0 && env[i][key_len] == '=')
		{
			res = ft_strdup(&env[i][key_len + !start + start]);
			ft_memdel((void*)&key);
			return (res);
		}
	}
	ft_memdel((void*)&key);
	return (ft_strdup(""));
}

char	*replace_tild(char *token, char **env)
{
	char *res;

	res = get_corresponding_env_setting(ft_strdup("HOME"), env, 0);
	if (!*res)
		error_not_set("HOME");
	ft_memdel((void*)&token);
	return (res);
}

char	**parse_input(char *value, char **env)
{
	char			**res;
	unsigned int	i;

	res = ft_strsplit(value, " 	");
	i = -1;
	while (res[++i])
	{
		if (res[i][0] == '$')
			res[i] = get_corresponding_env_setting(res[i], env, 1);
		else if (res[i][0] == '~')
			res[i] = replace_tild(res[i], env);
	}
	return (res);
}

int		main(int argc, char **argv, char **env)
{
	char	*cmd;
	char	**cmd_argv;
	char	***mini_env;
	char	**copy_env;

	if (argc > 1)
		error_argv(argv);
	else
	{
		copy_env = cpy_2d_strarray(env);
		mini_env = &copy_env;
		while (1)
		{
			cmd = ft_strnew(INIT_MALL_SIZE);
			print_prompt();
			read_stdin(&cmd, *mini_env);
			if (!*cmd)
			{
				ft_memdel((void*)&cmd);
				continue ;
			}
			cmd_argv = parse_input(cmd, *mini_env);
			ft_memdel((void*)&cmd);
			handle_cmd(cmd_argv, mini_env);
		}
	}
	return (0);
}
