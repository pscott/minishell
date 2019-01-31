/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:57:51 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 17:59:23 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int		error_fork(void)
{
	ft_putstr_fd("Error: could not fork\n", 2);
	exit(1);
}

char	*error_mem(void)
{
	ft_putstr_fd("Error: failed to allocate memory\n", 2);
	exit(1);
	return (NULL);
}
