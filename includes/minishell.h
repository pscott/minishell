/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:21:36 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 21:38:20 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "unit_test.h"
# include "errors.h"

# define INIT_SIZE 4

void	print_prompt(void);
void	print_env(char **env);
void	print_exit(void);

int		should_i_exit(char **argv);
void	parse_cmd(char *cd, char **env);
char	*append_path(char *origin, char *append);
void	free_strarray(char **argv);

#endif
