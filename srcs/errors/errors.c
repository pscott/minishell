/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 12:47:17 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 13:30:20 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int		error_fork(void)
{
	ft_putstr_fd("Error: could no fork.\n", 2);
	exit(1);
}

int		error_mem(void)
{
	ft_putstr_fd("Error: failed to allocate memory\n", 2);
	exit(1);
}

int		error_read(void)
{
	ft_putstr_fd("Error: failed to read\n", 2);
	exit(1);
}
