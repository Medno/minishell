# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 11:04:53 by pchadeni          #+#    #+#              #
#    Updated: 2018/01/23 13:25:48 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
C_FLAGS = -Wall -Wextra -Werror
FILES = ft_atoi.c \
		ft_bzero.c \
		ft_case.c \
		ft_checkopt.c \
		ft_foreachint.c \
		ft_getopt.c \
		ft_ischar.c \
		ft_isx.c \
		ft_itoa.c \
		ft_lastchar.c \
		ft_lstalloc.c \
		ft_lstmanip.c \
		ft_maths.c \
		ft_memalloc.c \
		ft_memmanip.c \
		ft_nbchar.c \
		ft_nbwords.c \
		ft_put.c \
		ft_put_fd.c \
		ft_putcolor.c \
		ft_putsgap.c \
		ft_putformat.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strgap.c \
		ft_striter.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strnew.c \
		ft_splitwsp.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tab.c \
		get_next_line.c

OBJ = $(FILES:.c=.o)
NAME = libft.a


all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[01;32mLibft compiled ✓\033[22;0m"

%.o : %.c
	@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) $(C_FLAGS) -c $< -I libft.h

clean:
	@rm -Rf $(OBJ)
	@echo "\033[01;32mLibft clean ✓\033[22;0m"

fclean: clean
	@rm -Rf $(NAME)
	@echo "\033[01;32mLibft fclean ✓\033[22;0m"

re: fclean all
