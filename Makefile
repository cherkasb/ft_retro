# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/18 14:04:05 by bcherkas          #+#    #+#              #
#    Updated: 2018/06/24 20:57:19 by bcherkas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME=ft_retro

CC=clang++

CFLAGS=-Wall -Wextra -Werror

CLASSES=Bullet.cpp Enemy.cpp Ghost.cpp Hero.cpp Player.cpp Space_invaders.cpp WindowMenu.cpp

FILES=main.cpp $(CLASSES)

OBJS=$(FILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
