/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:19:48 by pscott            #+#    #+#             */
/*   Updated: 2019/02/11 16:57:15 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "libft.h"
# define ERR_FORK error_fork()
# define ERR_MEM error_mem()
# define ERR_READ error_read()
# define ERR_NOENT error_noent
# define ERR_EXIST error_exist

void	error_read(void);
char	*error_mem(void);
int		error_fork(void);
void	error_noent(char *cmd, char *str);
void	error_exist(char *cmd);

void	error_cmd_not_found(char *cmd);
int		error_permi(char *cmd, char *str);
int		error_arguments(void);
void	error_numeric(char *str);
void	error_no_pwd(char *str);
void	error_not_set(char *key);
void	error_argv(char **argv);
void	error_exit(char *cmd, char **env);
void	free_cmd_env(char *cmd, char **env);

#endif
