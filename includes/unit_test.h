/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_test.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:41:00 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 21:41:01 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TEST_H
# define UNIT_TEST_H

# include <unistd.h>
# define MALLOC return_null()
# define FORK fork()

void	*return_null(int size);
pid_t	return_int(void);

#endif
