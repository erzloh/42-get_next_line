# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eholzer <eholzer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 08:45:09 by eholzer           #+#    #+#              #
#    Updated: 2022/11/18 16:11:56 by eholzer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	get_next_line.c \
			get_next_line_utils.c \

OBJS	=	$(SRCS:.c=.o)

NAME	=	gnl

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra -D BUFFER_SIZE=42

all:		$(NAME)

$(NAME):	$(OBJS)
#			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
			ar rcs ${NAME} ${OBJS}

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

test:		$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

.PHONY:		all clean fclean re