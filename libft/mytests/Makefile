CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB_DIR = $(shell dirname $(shell pwd))
LIBFT = $(LIB_DIR)/libft.a
INCLUDES = -I$(LIB_DIR) -I.
TEST_PATH = .
TEST_SRC = $(foreach D, $(TEST_PATH), $(wildcard $(D)/*.c))
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))
NAME = test_all

all: test

test: $(NAME)
	@./$(NAME) && rm -f $(NAME)

$(NAME): $(TEST_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(TEST_OBJ) $(LIBFT) -o $@

$(LIBFT):
	make -C $(LIB_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@rm -f $(TEST_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
