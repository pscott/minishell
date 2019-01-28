/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:01:16 by pscott            #+#    #+#             */
/*   Updated: 2019/01/28 17:01:33 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ret < 0)
		ERR_READ;
	if (!(**cmd))
	{
		ft_memdel((void*)cmd);
		if (ret == 0)
		{
			ft_putstr_fd("exit\n", 2);
			exit(0);
		}
	}
}

int		main(int argc, char **argv, char **env)
{
	char	*cmd;
	char	**cmd_argv;

	(void)argc;
	(void)argv;
	while (1)
	{
		cmd = ft_strnew(INIT_MALL_SIZE);
		print_prompt();
		read_stdin(&cmd, env);
		if (!cmd)
			continue ;
		cmd_argv = ft_strsplit(cmd, " 	");
		ft_memdel((void*)&cmd);
		handle_cmd(cmd_argv, env);
	}
	return (0);
}
