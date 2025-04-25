CC = cc
CFLAGS = -Wall -Wextra -Werror -D_DEFAULT_SOURCE
LIB_DIR = $(shell dirname $(shell pwd))
LIBFT = $(LIB_DIR)/libft.a
INCLUDES = -I$(LIB_DIR) -I.
TEST_PATH = .
TEST_SRC = $(foreach D, $(TEST_PATH), $(wildcard $(D)/*.c))
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))
VAL = valgrind --tool=memcheck --trace-children=yes --track-origins=yes --show-leak-kinds=all --leak-check=full
NAME = test_all.out

all: test

test: $(NAME)
	@$(VAL) ./$(NAME)

$(NAME): $(TEST_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -lbsd

cleanlib:
	make fclean -C $(LIB_DIR)

$(LIBFT):
	make re -C $(LIB_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@rm -f $(TEST_OBJ)

fclean: clean cleanlib
	@rm -f $(NAME)

re: fclean all
