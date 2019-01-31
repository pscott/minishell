/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:21:36 by pscott            #+#    #+#             */
/*   Updated: 2019/01/31 14:42:43 by pscott           ###   ########.fr       */
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

/* 
 * BUILTINS
*/

void	execute_command(char *possible_path, char **argv, char **env);
int		mini_cd(char **cmd_argv, char **env);
int		mini_exit(char **argv, char **env);
int		mini_setenv(char **argv, char ***env);
int		mini_env(char **argv, char **env);
int		mini_unsetenv(char **argv, char **env);


/*
** env
*/

int				is_env_setting(char *str);
unsigned int	get_var_len(char *str);
int				setting_is_in_env(char *str, char **env);
unsigned int	how_many_new_env_var(char **argv, char **env,
		unsigned int *settings);
void			append_new_env(char *str, char **env);
void			modify_existing_env(char *str, char **env);
void			add_envs(char **argv, char **env);
char			**parse_env(char **argv, char **env, unsigned int *settings);

int		check_access(char *path);
void	clean_exit(char **cmd_argv, char **env, int exit_value);
void	handle_cmd(char **cd, char ***env);
void	get_path(char *cmd, char **env, char *posibble_path);
void	join_path(char *dst, char *origin, char *append);
void	free_strarray(char **argv);

int		handle_builtin(char **cmd_argv, char ***env);

int		slash_in_cmd(char *cmd);

void	free_cmd_env(char *cmd, char **env);
void	free_argv_env(char **cmd_argv, char **env);

char	*get_corresponding_env_setting(char *env_name, char **env,
		unsigned int start);

#endif
