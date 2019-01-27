# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pscott <pscott@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/26 18:25:41 by pscott            #+#    #+#              #
#    Updated: 2019/01/27 13:24:31 by pscott           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= gcc
WFLAGS	:= -Wall -Wextra
RM		:= rm -rf
NAME	:= minishell

OBJDIR			:= objects
SRCDIR			:= srcs
UNIT_TESTDIR	:= $(SRCDIR)/unit_test
ERRDIR			:= $(SRCDIR)/errors

SRC			:= main.c
UNIT_TEST	:= returns.c
ERR			:= errors.c

INCL	:= -I includes/ -I libft/includes

LIBS	:= -L libft -lft
SRCS	:= $(addprefix $(SRCDIR)/, $(SRC))
ERRS	:= $(addprefix $(ERRDIR)/, $(ERR))
U_TESTS	:= $(addprefix $(UNIT_TESTDIR)/, $(UNIT_TEST))
MINI	:= $(SRCS) $(U_TESTS) $(ERRS)

OBJS	:= $(MINI:.c=.o)
DEPS	:= includes/minishell.h includes/unit_test.h includes/errors.h

COMP	:= $(CC) $(WFLAGS) $(INCL) $(LIBS)
OPT		:=

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft -j

d: all
	@./$(NAME) $(OPT)

val:
	@$(COMP) -o $(NAME) $(MINI) -g
	valgrind --leak-check=full ./$(NAME)

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
