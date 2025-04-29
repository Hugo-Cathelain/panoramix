##
## EPITECH PROJECT, 2025
## day-04
## File description:
## Makefile
##

CC			=	gcc

INCLUDES	=	-Iinclude
CCFLAGS		=	-Wall -Wextra
FLAGS		=	$(INCLUDES) $(CCFLAGS) $(LDFLAGS)

DIRECTORY   =	src

SOURCES		=	$(shell find $(DIRECTORY) -type f -iname "*.c")
OBJECTS		=	$(SOURCES:.c=.o)

TARGET		=	panoramix

all: $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@ $(FLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(FLAGS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

re: fclean all
