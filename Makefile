##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Simple description
##

DIR		=	src

$(CC)	=	gcc

CFLAGS	+=	-Wall -Wextra -Werror -g -I./header/

FILE    =   $(shell find $(DIR) -maxdepth 2 -name '*.c')

OBJ		= $(FILE:.c=.o)

FILENAME	=	myftp

all: $(OBJ)
	@$(CC) $(OBJ) -o $(FILENAME) $(CFLAGS)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(FILENAME)

re:	fclean	all

build: all

.PHONY: all clean fclean re build
