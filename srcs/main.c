/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:01:16 by pscott            #+#    #+#             */
/*   Updated: 2019/01/29 19:45:02 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_env(char *cmd, char **env)
{
	ft_memdel((void*)cmd);
	free_strarray(env);
}

char	**cpy_2d_strarray(char **env)
{
	int		i;
	char	**res;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	if (!(res = (char**)MALLOC(sizeof(*res) * (i + 1))))
		ERR_MEM;
	res[i] = NULL;
	i = -1;
	while (env[++i])
		res[i] = ft_strdup(env[i]);
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
	while ((ret = read(0, &buf, 1) > 0) && buf != '\n')
	{
		*cmd = ft_realloc((void*)*cmd, ft_strlen(*cmd), &mall_size, ret);
		ft_strncat((*cmd + i++), &buf, 1);
	}
	ft_printf("OUI\n");
	if (buf == '\n')
		return ;
	else if (ret == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	else if (ret < 0)
		ERR_READ;
}

int		main(int argc, char **argv, char **env)
{
	char	*cmd;
	char	**cmd_argv;
	char	***mini_env;
	char	**copy_env;

	(void)argc;
	(void)argv;
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
		cmd_argv = ft_strsplit(cmd, " 	");
		ft_memdel((void*)&cmd);
		handle_cmd(cmd_argv, mini_env);
	}
	return (0);
}
