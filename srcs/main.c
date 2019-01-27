/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:17:27 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 21:33:22 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*reset_params(char **cmd, int *i, size_t *mall_size)
{
	char *tmp;

	if (!*cmd || **cmd == 0)
	{
		print_prompt();
		return (*cmd);
	}
	*i = 0;
	*mall_size = INIT_SIZE;
	tmp = ft_strnew(*mall_size);
	ft_memdel((void*)cmd);
	print_prompt();
	return (tmp);
}

void	read_stdin(char **cmd, char **env)
{
	int		ret;
	char	buf;
	int		i;
	size_t	mall_size;

	mall_size = INIT_SIZE;
	i = 0;
	while ((ret = read(0, &buf, 1) > 0))
	{
		if (buf == '\n')
		{
			parse_cmd(*cmd, env);
			*cmd = reset_params(cmd, &i, &mall_size);
			continue ;
		}
		*cmd = ft_realloc((void*)*cmd, ft_strlen(*cmd), &mall_size, ret);
		ft_strncat((*cmd + i++), &buf, 1);
	}
	if (ret == -1)
		ERR_READ;
}

int		main(int argc, char **argv, char **env)
{
	char	*cmd;
	int		i;

	(void)argc;
	(void)argv;
	i = 0;
	cmd = ft_strnew(INIT_SIZE);
	print_prompt();
	read_stdin(&cmd, env);
	ft_putstr_fd("exit\n", 2);
	ft_memdel((void*)&cmd);
	return (0);
}
