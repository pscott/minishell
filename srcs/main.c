/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:17:27 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 18:45:06 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_strarray(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		ft_memdel((void*)&argv[i]);
		i++;
	}
	ft_memdel((void*)&argv);
}

void	parse_cmd(char *cmd)
{
	char	**argv;
	int		i;
	pid_t	child_pid;

	if (*cmd == 0)
		return ;
	argv = ft_strsplit(cmd, ' ');
	if (should_i_exit(argv) == -1)
		return ;
	i = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd, argv, NULL);
		ERR_EXEC(*argv);
	}
	else if (child_pid == -1)
		ERR_FORK;
	else
		wait(&child_pid);
	free_strarray(argv);
}

char	*reset_params(char *cmd, int *i, size_t *mall_size)
{
	char *tmp;

	*i = 0;
	*mall_size = INIT_SIZE;
	tmp = ft_strnew(*mall_size);
	ft_memdel((void*)&cmd);
	print_prompt();
	return (tmp);
}

int		main(void)
{
	int		ret;
	char	buf;
	char	*cmd;
	int		i;
	size_t	mall_size;

	mall_size = INIT_SIZE;
	i = 0;
	cmd = ft_strnew(mall_size);
	print_prompt();
	while ((ret = read(0, &buf, 1) > 0))
	{
		if (buf == '\n')
		{
			parse_cmd(cmd);
			cmd = reset_params(cmd, &i, &mall_size);
			continue ;
		}
		cmd = ft_realloc((void*)cmd, ft_strlen(cmd), &mall_size, ret);
		ft_strncat((cmd + i++), &buf, 1);
	}
	if (ret == -1)
		return (ERR_READ);
	ft_memdel((void*)&cmd);
	return (0);
}
