/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:43:53 by pscott            #+#    #+#             */
/*   Updated: 2019/02/11 17:02:43 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_stdin(char **cmd, char **env)
{
	int		ret;
	char	buf;
	int		i;
	size_t	mall_size;

	print_prompt();
	mall_size = INIT_MALL_SIZE;
	i = 0;
	buf = 0;
	while ((ret = read(0, &buf, 1) > 0) && buf && buf != '\n')
	{
		*cmd = ft_realloc((void*)*cmd, ft_strlen(*cmd), &mall_size, ret);
		ft_strncat((*cmd + i++), &buf, 1);
	}
	if (buf == '\n')
		return ;
	else if (ret == 0)
		error_exit(*cmd, env);
	else if (ret < 0 || (!buf && ret))
		ERR_READ;
}

char	**parse_input(char *input, char **env)
{
	char			**res;
	int				i;
	int				j;

	if (ft_strchr(input, ';'))
	{
		ft_memdel((void*)(&input));
		return (NULL);
	}
	res = ft_strsplit(input, " 	");
	i = -1;
	while (res[++i])
	{
		j = 0;
		while (res[i][j])
		{
			if (res[i][j] == '$')
				res[i] = replace_dollar(res[i], env, j);
			j++;
		}
		if (res[i][0] == '~')
			res[i] = replace_tild(res[i], env);
	}
	ft_memdel((void*)&input);
	return (res);
}

int		main(int argc, char **argv, char **env)
{
	char	*input;
	char	**cmd_argv;
	char	***mini_env;
	char	**copy_env;

	if (argc < 1)
		error_argv(argv);
	else
	{
		copy_env = cpy_2d_strarray(env);
		mini_env = &copy_env;
		while (1)
		{
			input = ft_strnew(INIT_MALL_SIZE);
			read_stdin(&input, *mini_env);
			if (!*input)
			{
				ft_memdel((void*)&input);
				continue ;
			}
			cmd_argv = parse_input(input, *mini_env);
			handle_cmd(cmd_argv, mini_env);
		}
	}
	return (0);
}
