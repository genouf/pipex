# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: genouf <genouf@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 22:28:16 by genouf            #+#    #+#              #
#    Updated: 2022/06/19 15:56:48 by genouf           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	sources/pipex.c				\
		sources/find_path.c			\
		sources/utils.c				\
		
OBJS = ${SRCS:.c=.o}

BONUS = sources/pipex_bonus.c 		\
		sources/find_path_bonus.c 	\
		sources/utils_bonus.c 		\
		sources/pipex_tools_bonus.c \
		
OBJS_BONUS = ${BONUS:.c=.o}

INC =	pipex.h	

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

bonus : pipex_bonus

pipex_bonus : ${OBJS_BONUS} ${LIBA}
		${CC} -g -o $@ ${OBJS_BONUS} ${LIB} 

/%.o:	%.c
		${CC} ${CFLAGS} -c $@ $<

skiperror: ${OBJS} ${LIBA}
		${CC} -o ${NAME} ${SRCS} -g ${LIB}

fsa: ${OBJS} ${LIBA}
		${CC} -fsanitize=address ${CFLAGS} -o $@ ${SRCS} ${LIB}

clean:
		${RM} ./${OBJS} ./${OBJS_BONUS}
		${MAKE} clean
		@echo "cleaning .o files"

fclean: clean
		${RM} ${NAME} pipex_bonus
		${MAKE} fclean
		
re:		fclean all		