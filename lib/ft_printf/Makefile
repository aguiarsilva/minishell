# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 13:00:46 by tbui-quo          #+#    #+#              #
#    Updated: 2023/01/25 14:48:10 by tbui-quo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
# Name of the compiled program

#SRCS = ft_printf.c ft_utils.c get_next_line/*.c
SRCS = ft_printf.c ft_utils.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
# List all .c files to be compiled

OBJS = ${SRCS:.c=.o}
# To compile only changed .c files into .o files

LIBFT_DIR = ../libft
# Relative path to the libft directory

OBJS_SUB = $(shell find $(LIBFT_DIR) -type f -name "*.o")
# List all .o files in the libft directory

RM = rm -f
# -f (force) makes fclean executable at any time (even without .o files)

CC = cc
# Compilation language
CFLAGS = -Wall -Wextra -Werror

MAIN = main.c

MAGENTA = \033[0;95m

all: ${NAME}

# The flags used
${NAME}: makelibft ${OBJS}
	ar rcs ${NAME} ${OBJS} ${OBJS_SUB}

compile:
	$(CC) $(MAIN) $(NAME)

makelibft:
	@echo "$(MAGENTA)Compiling libft:"
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a ${NAME}

clean:
	${RM} ${OBJS}
	make -C $(LIBFT_DIR) clean


fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
