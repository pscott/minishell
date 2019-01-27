/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:18:02 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 21:37:40 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_path(char *origin, char *append)
{
	int		origin_len;
	int		append_len;
	char	*res;

	if (!append)
		return (origin);
	if (!origin)
		return (append);
	origin_len = ft_strlen(origin);
	append_len = ft_strlen(append);
	res = ft_strnew(origin_len + append_len + 1);
	ft_strncpy(res, origin, origin_len);
	res[origin_len] = '/';
	ft_strncpy(res + origin_len + 1, append, append_len);
	return (res);
}

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
