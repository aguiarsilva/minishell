# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    older_Makefile_with_also_works                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 13:08:00 by tbui-quo          #+#    #+#              #
#    Updated: 2023/01/20 15:37:13 by tbui-quo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c			\
		ft_bzero.c			\
		ft_memcpy.c			\
		ft_memmove.c 		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_strlen.c			\
		ft_isalpha.c 		\
		ft_isdigit.c		\
		ft_isalnum.c		\
		ft_isascii.c		\
		ft_isprint.c		\
		ft_toupper.c		\
		ft_tolower.c		\
		ft_strcat.c			\
		ft_strchr.c			\
		ft_striteri.c		\
		ft_strrchr.c		\
		ft_strncmp.c		\
		ft_strlcpy.c		\
		ft_strlcat.c		\
		ft_strnstr.c		\
		ft_atoi.c			\
		ft_calloc.c			\
		ft_strdup.c			\
		ft_substr.c			\
		ft_strjoin.c 		\
		ft_strtrim.c		\
		ft_split.c			\
		ft_itoa.c			\
		ft_strmapi.c		\
		ft_putchar_fd.c		\
		ft_putstr_fd.c		\
		ft_putendl_fd.c		\
		ft_putnbr_fd.c		\
		ft_count_words.c		\
		ft_max.c		\
		ft_min.c		\
		ft_fabs.c		\
		ft_abs.c \
		ft_atoll.c

BSRC = ft_lstnew.c			\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstclear.c		\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\

OBJS = ${SRC:.c=.o}
BOBJS = ${BSRC:.c=.o}

CC = gcc
CFLAGS = -Wall -Werror -Wextra

all:	${NAME}

${NAME}: ${OBJS}
		${CC} ${CFLAGS} -c ${SRC}
		ar rcs ${NAME} ${OBJS}

bonus: $(OBJS) $(BOBJS)
		${CC} ${CFLAGS} -c ${BSRC}
		ar rcs ${NAME} ${OBJS} ${BOBJS}

	
clean:
	rm -f ${OBJS} ${BOBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean bonus re
