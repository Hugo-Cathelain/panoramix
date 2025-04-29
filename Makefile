##
## EPITECH PROJECT, 2025
## day-04
## File description:
## Makefile
##

SRC = main.c

OBJ = $(SRC:.c=.o)

NAME = panoramix

FLAGS = -Wall -Wextra -std=gnu17

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) -Iinclude $(FLAGS) -g3

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
