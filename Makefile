CC = cc
NAME = ft_ping
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE = -Iincludes
DIR = obj
SRC = src/main.c \
	  src/utils.c \
	  src/ft_ping.c

OBJ = $(SRC:src/%.c=$(DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME)

$(DIR)/%.o: src/%.c
	@mkdir -p $(DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "ft_ping compiled"

clean:
	@rm -rf $(DIR)

fclean: clean
	@rm $(NAME)

re: fclean all

.PHONY: clean fclean all


