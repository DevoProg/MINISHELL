NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror
SOURCE = sources/main.c sources/ft_split_cmd.c sources/ft_error.c sources/init_struct.c
OBJ = $(SOURCE:.c=.o)

%.o: %.c
	cd libft && make bonus && make
	cd ..
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -lreadline  libft/libft.a $(OBJ) -o $(NAME)

clean:
	cd libft && make clean
	cd ..
	rm -f $(OBJ)

fclean: clean
	cd libft && make fclean
	cd ..
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
