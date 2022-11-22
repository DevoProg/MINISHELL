NAME = minishell

SRCS = sources/main.c

INCLUDES = includes

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

CC = gcc

$(RM) = rm -rf

.c.o: $(SRC)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c -o $@ $<
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $@
	
all: $(NAME)

clean:
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean clean

.PHONY: all clean fclean re
