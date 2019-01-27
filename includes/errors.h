/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 12:45:39 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 16:15:13 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# include "libft.h"
# define ERRORS_H

# define ERR_FORK error_fork()
# define ERR_MEM error_mem()
# define ERR_READ error_read()
# define ERR_EXEC error_execve

int		error_read(void);
int		error_mem(void);
int		error_fork(void);
void	error_execve(char *str);

#endif
