NAME = fillit
CFLAGS =  -Wall -Werror -Wextra

SRC = ./fillit.c \
	./valid.c \
	./main.c \
	./libft.c 

OBJ	= $(patsubst src/%.c,./%.o,$(SRC))

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -c $(SRC)
	gcc $(CFLAGS) $(OBJ) -o $(NAME)

re: fclean all

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
