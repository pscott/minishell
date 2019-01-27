/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_testing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 12:40:37 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 13:29:58 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TESTING_H
# include <unistd.h>
# define UNIT_TESTING_H

# define MALLOC return_null()
# define FORK fork()

void	*return_null(int size);
pid_t	return_int(void);

#endif
