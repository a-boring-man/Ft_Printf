# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrinna <jrinna@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 09:39:16 by jrinna            #+#    #+#              #
#    Updated: 2021/11/19 09:59:09 by jrinna           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c

OBJ = $(SRCS:.c=.o)

NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

${NAME}: ${OBJ}
	${MAKE} -C ./libft
	cp ./libft/libft.a ${NAME}
	ar rcs ${NAME} ${OBJ} 

%.o : %.c Makefile ft_printf.h
	$(CC) $(CFLAG) -c -o $@ $<

all : ${NAME}

bonus : ${NAME}

clean :
	${MAKE} clean -C ./libft
	$(RM) ${OBJ}

fclean : clean
	${MAKE} fclean -C ./libft
	$(RM) $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all
