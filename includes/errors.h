/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 12:45:39 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 13:03:39 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# include "libft.h"
# define ERRORS_H

# define ERR_FORK error_fork()
# define ERR_MEM error_mem()
# define ERR_READ error_read()

int		error_read(void);
int		error_mem(void);
int		error_fork();

#endif
