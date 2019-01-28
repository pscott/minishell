/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:21:36 by pscott            #+#    #+#             */
/*   Updated: 2019/01/28 19:01:09 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/syslimits.h>
# include "ft_printf.h"
# include "unit_test.h"
# include "errors.h"

# define INIT_MALL_SIZE 8

void	print_prompt(void);
void	print_env(char **env);
void	print_exit(void);

int		mini_exit(char **argv);
void	clean_exit(char **cmd_argv, int exit_value);
void	handle_cmd(char **cd, char **env);
void	join_path(char *dst, char *origin, char *append);
void	free_strarray(char **argv);

int		handle_builtin(char **cmd_argv, char **env);

int		slash_in_cmd(char *cmd);

#endif
