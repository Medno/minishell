# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:57:58 by pchadeni          #+#    #+#              #
#    Updated: 2018/01/11 18:32:34 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------Compilation's flags------#

CC = gcc
C_FLAGS = -Wall -Wextra -Werror

#------Name of the exec------#

NAME = minishell

#------All sources------#

SRC = error.c \
	  echo_new.c \
	  env.c \
	  main.c \
	  cd_new.c \
	  line.c

OBJ = $(SRC:.c=.o)

#------Path------#

SRCPATH = src
OPATH = obj

OBJP = $(addprefix $(OPATH)/, $(SRC:.c=.o))

#------Library------#

LIB = ./libft/libft.a

#------Define colors------#

BOLD_GREEN = \033[01;32m
COL_GREEN = \033[0;32m
COL_YELLOW = \033[0;33m
END_COL = \033[0m

#------Main rules------#

all: $(LIB) $(OPATH) $(NAME)

re: fclean all

#------Compilation of Libft------#

$(LIB) : 
	@$(MAKE) -C libft/ MAKEFLAGS=

####### Do not edit, main rules #######

$(OPATH)/%.o: $(SRCPATH)/%.c
	@$(CC) $(C_FLAGS) -o $@ -c $^
	@echo " $(COL_GREEN)[OK]$(END_COL)    $(COL_YELLOW)Compiling:$(END_COL)" $<

$(OPATH):
	@mkdir -p $(OPATH)

$(NAME): $(OBJP)
	@$(CC) $^ $(LIB) -o $@
	@echo "$(BOLD_GREEN)$(NAME) created ✓$(END_COL)"

clean:
	@$(MAKE) clean -C libft/
	@rm -Rf $(OPATH)
	@echo "$(BOLD_GREEN)$(NAME) clean ✓$(END_COL)"

fclean: clean
	@$(MAKE) fclean -C libft/
	@rm -Rf $(NAME)
	@echo "$(BOLD_GREEN)$(NAME) fclean ✓$(END_COL)"
