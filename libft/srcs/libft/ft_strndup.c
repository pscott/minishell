/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 09:36:59 by pscott            #+#    #+#             */
/*   Updated: 2019/02/11 16:27:28 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1) > n ? ft_strlen(s1) : n;
	if (!res = ft_strnew(len))
		return (NULL);
	return (ft_strncpy(res, s1, len));
}
