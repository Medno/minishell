# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 11:04:53 by pchadeni          #+#    #+#              #
#    Updated: 2018/01/29 17:35:45 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------Compilation's flags------#

CC = gcc
C_FLAGS = -Wall -Wextra -Werror

#------Name of the lib------#

NAME = libft.a

#------All sources------#

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

#------Define colors------#

BOLD_GREEN = \033[01;32m
COL_GREEN = \033[0;32m
COL_YELLOW = \033[0;33m
END_COL = \033[0m

#------Main rules------#

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(BOLD_GREEN) Libft compiled ✓$(END_COL)"

%.o : %.c
	@echo -n '>'
	@$(CC) $(C_FLAGS) -c $< -I libft.h

clean:
	@rm -Rf $(OBJ)
	@echo "$(COL_GREEN)Libft clean ✓$(END_COL)"

fclean: clean
	@rm -Rf $(NAME)
	@echo "$(COL_GREEN)Libft fclean ✓$(END_COL)"

re: fclean all
