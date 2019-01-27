/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:17:27 by pscott            #+#    #+#             */
/*   Updated: 2019/01/27 13:31:57 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	childprocess(pid_t pid)
{
	char *argv[] = {"/bin/sh", "-l", NULL};
	ft_printf("I'm a child: %d\n", pid);
	execve(argv[0], argv, NULL);
}

void	fatherprocess(pid_t pid)
{
	ft_printf("And faaather: %d\n", pid);
}

void	print_prompt(void)
{
	write(1, "$> ", 3);
}
/*int		main(void)
  {
  pid_t	pid;

  if ((pid = FORK) == -1)
  return (error_fork());
  if (pid == 0)
  childprocess(pid);
  else if (pid > 0)
  fatherprocess(pid);
  else
  return (error_fork());
  return (0);
  }*/

int		main(void)
{
	int		ret;
	char	buf;
	char	*str;
	int		i;
	size_t	mall_size;

	mall_size = INIT_SIZE;
	i = 0;
	if (!(str = ft_strnew(mall_size)))
		return (ERR_MEM);
	print_prompt();
	while ((ret = read(0, &buf, 1) > 0))
	{
		if (buf == '\n')
		{
			print_prompt();
			ft_bzero(str, ft_strlen(str));
			i = 0;
			mall_size = INIT_SIZE;
			continue ;
		}
		if (!(str = ft_realloc((void*)str, ft_strlen(str), &mall_size, ret)))
			ERR_MEM;
		ft_strcat((str + i++), &buf);
	}
	if (ret == -1)
		return (ERR_READ);
	ft_printf("%s\n", str);
	ft_memdel((void*)&str);
	return (0);
}
