/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:17:27 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 18:09:43 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	write(1, "$> ", 3);
}

/*int runcmd(char *cmd)
  {
  char *argv[MAX_ARGS];
  pid_t child_pid;
  int child_status;

  parsecmd(cmd,argv);
  child_pid = fork();
  if(child_pid == 0) {
  This is done by the child process.

  execvp(argv[0], argv);

  If execvp returns, it must have failed.

  printf("Unknown command\n");
  exit(0);
  }
  else {
  This is run by the parent.  Wait for the child
  to terminate. 

  do {
  pid_t tpid = wait(&child_status);
  if(tpid != child_pid) process_terminated(tpid);
  } while(tpid != child_pid);

  return child_status;
  }
  }*/

int		is_num(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int		check_exit(char **argv)
{
	int i;

	if (!argv)
		return (0);
	i = 0;
	if (*argv && ft_strcmp(argv[i], "exit") == 0)
	{
		ft_putstr_fd(argv[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
		if (argv[i])
		{
			if (is_num(argv[i]))
			{
				if (argv[i  + 1])
				{
					ft_putstr_fd("minishell: exit: too many arguments\n", 2);
					return (1);
				}
				exit(ft_atoi(argv[i]));
			}
			if (!is_num(argv[i]))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(-1);
			}
		}
		exit(0);
	}
	return (0);
}

void	free_strarray(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		ft_memdel((void*)&argv[i]);
		i++;
	}
	ft_memdel((void*)&argv);
}

void	parse_cmd(char *cmd)
{
	char	 **argv;
	char	 *env[3];
	int		 i;
	pid_t	child_pid;

	if (*cmd == 0)
		return ;
	argv = ft_strsplit(cmd, ' ');
	if (check_exit(argv) == -1)
		return ;
	i = 0;
	env[0] = "/bin";
	env[1] = "/usr/bin";
	env[2] = NULL;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd, argv, env);
		ERR_EXEC(*argv);
	}
	else if (child_pid == -1)
		ERR_FORK;
	else
		wait(&child_pid);
	free_strarray(argv);
}

char	*reset_params(char *cmd, int *i, size_t *mall_size)
{
	char *tmp;

	*i = 0;
	*mall_size = INIT_SIZE;
	if (!(tmp = ft_strnew(*mall_size)))
		ERR_MEM;
	ft_memdel((void*)&cmd);
	return (tmp);
}

int		main(void)
{
	int		ret;
	char	buf;
	char	*cmd;
	int		i;
	size_t	mall_size;

	mall_size = INIT_SIZE;
	i = 0;
	if (!(cmd = ft_strnew(mall_size)))
		ERR_MEM;
	print_prompt();
	while ((ret = read(0, &buf, 1) > 0))
	{
		if (buf == '\n')
		{
			parse_cmd(cmd);
			cmd = reset_params(cmd, &i, &mall_size);
			print_prompt();
			continue ;
		}
		if (!(cmd = ft_realloc((void*)cmd, ft_strlen(cmd), &mall_size, ret)))
			ERR_MEM;
		ft_strncat((cmd + i++), &buf, 1);
	}
	if (ret == -1)
		return (ERR_READ);
	ft_printf("%s\n", cmd);
	ft_memdel((void*)&cmd);
	return (0);
}
