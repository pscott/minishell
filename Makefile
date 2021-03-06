# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pscott <pscott@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 18:25:41 by pscott            #+#    #+#              #
#    Updated: 2019/02/11 16:28:23 by pscott           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
WFLAGS	:= -Wall -Wextra
RM		:= rm -rf
NAME	:= minishell

OBJDIR			:= objects
SRCDIR			:= srcs
ERRDIR			:= $(SRCDIR)/errors
BUILTINDIR		:= $(SRCDIR)/builtins

SRC			:= main.c utils.c cmd_handling.c print_helper.c env_helper.c \
	execute.c init_helper.c free.c expands.c
BUILTIN		:= builtin.c exit.c env.c setenv.c unsetenv.c cd.c echo.c
ERR			:= critical_errors.c error_only_print.c error_w_exit.c \
   error_w_return.c

INCL	:= -I includes/ -I libft/includes

LIBS		:= -L libft -lft
SRCS		:= $(addprefix $(SRCDIR)/, $(SRC))
ERRS		:= $(addprefix $(ERRDIR)/, $(ERR))
BUILTINS	:= $(addprefix $(BUILTINDIR)/, $(BUILTIN))
MINI		:= $(SRCS) $(U_TESTS) $(ERRS) $(BUILTINS)

OBJS	:= $(MINI:.c=.o)
DEPS	:= includes/minishell.h includes/unit_test.h includes/errors.h

COMP	:= $(CC) $(WFLAGS) $(INCL) $(LIBS)
OPT		:=

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft -j

d: all
	@./$(NAME)

val: all
	@$(COMP) -o $(NAME) $(MINI) -g
	valgrind --leak-check=full ./$(NAME)

fsa:
	@$(COMP) -o $(NAME) $(MINI) -fsanitize=address -g3
	@./$(NAME)

$(NAME): $(OBJS) libft/libft.a Makefile
	$(COMP) -o $(NAME) $(MINI)

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(WFLAGS) $(INCL)

clean:
	@make clean -C libft
	@$(RM) *dSYM*
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)
	@$(RM) a.out

re: fclean all

.PHONY: all clean fclean re d fsa val
