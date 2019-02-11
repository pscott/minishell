/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:28:08 by pscott            #+#    #+#             */
/*   Updated: 2019/02/11 16:30:59 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dollar(char *arg, int *doll_len)
{
	int		i;
	char	*res;

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
