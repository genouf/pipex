# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: genouf <genouf@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 22:28:16 by genouf            #+#    #+#              #
#    Updated: 2022/06/11 11:29:34 by genouf           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	pipex.c						\
		
OBJS = ${SRCS:.c=.o}

INC = 	pipex.h						\
		
NAME = pipex

RM = rm -f

CC = gcc
CFLAGS = -Wall -Wextra -Werror

MAKE = make -C libft
LIBA = libft/libft.a
LIB = -L ./libft -lft

all: ${NAME}

${LIBA}:
		${MAKE}

${NAME}: ${OBJS} ${LIBA}
		${CC} ${CFLAGS} -o $@ ${SRCS} ${LIB}

/%.o:	%.c
		${CC} ${CFLAGS} -c $@ $<

skiperror: ${OBJS} ${LIBA}
		${CC} -o ${NAME} ${SRCS} -g ${LIB}

fsa: ${OBJS} ${LIBA}
		${CC} -fsanitize=address ${CFLAGS} -o $@ ${SRCS} ${LIB}

clean:
		${RM} ./${OBJS}
		${MAKE} clean
		@echo "cleaning .o files"

fclean: clean
		${RM} ${NAME}
		${MAKE} fclean
		
re:		fclean all		