CC = cc
NAME = ft_ping
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -Iinclude
SRC = src/main.c \
	src/ping.c \
	src/utils.c

DIR = objs
OBJS = $(SRC:src/%.c=$(DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

$(DIR)/%.o: src/%.c
	@mkdir -p objs
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Project compiled"

clean:
	@rm -rf $(DIR)

fclean: clean
	@rm $(NAME)
	@echo "Project cleaned"

re: fclean all

.PHONY: clean fclean all