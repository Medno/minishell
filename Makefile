# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:57:58 by pchadeni          #+#    #+#              #
#    Updated: 2018/01/08 15:40:18 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
C_FLAGS = -Wall -Wextra -Werror
SRC = main.c
LIB = ./libft/libft.a
OBJ = $(addprefix $(OBJPATH)/, $(SRC:.c=.o))
OBJPATH = obj
NAME = minishell
SRCPATH = src

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	@$(CC) $(OBJ) $(LIB) -o $(NAME)
	@echo "\033[01;32m$(NAME) created √\033[22;0m"

$(LIB) : 
	@$(MAKE) -C libft/ MAKEFLAGS=

$(OBJPATH)/%.o : $(SRCPATH)/%.c $(OBJPATH)
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) $(C_FLAGS) -o $@ -c $<

$(OBJPATH) :
	@mkdir -p $@

clean:
	@$(MAKE) clean -C libft/
	@rm -Rf $(OBJPATH)
	@echo "\033[01;32m$(NAME) clean √\033[22;0m"

fclean: clean
	@$(MAKE) fclean -C libft/
	@rm -Rf $(NAME)
	@echo "\033[01;32m$(NAME) fclean √\033[22;0m"

re: fclean all
