CC = cc
CFLAGS = -Wall -Wextra -Werror -D_DEFAULT_SOURCE
LIB_DIR = $(shell dirname $(shell pwd))
LIBFT = $(LIB_DIR)/libft.a
INCLUDES = -I$(LIB_DIR) -I.
TEST_SRC = test_atoi.c \
test_bzero.c \
test_calloc.c \
test_isalnum.c \
test_isalpha.c \
test_isascii.c \
test_isdigit.c \
test_isprint.c \
test_itoa.c \
test_memchr.c \
test_memcmp.c \
test_memcpy.c \
test_memmove.c \
test_memset.c \
test_putchar_fd.c \
test_putendl_fd.c \
test_putnbr_fd.c \
test_putstr_fd.c \
test_split.c \
test_strchr.c \
test_strdup.c \
test_striteri.c \
test_strjoin.c \
test_strlcat.c \
test_strlcpy.c \
test_strlen.c \
test_strmapi.c \
test_strncmp.c \
test_strnstr.c \
test_strrchr.c \
test_strtrim.c \
test_substr.c \
test_tolower.c \
test_toupper.c \
main.c \

TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))
VAL = valgrind --tool=memcheck --trace-children=yes --track-origins=yes --show-leak-kinds=all --leak-check=full
FSAN = -fsanitize=address
NAME = test_all.out

all: test

test: $(NAME)
	@./$(NAME)

$(NAME): $(TEST_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ -lbsd $(FSAN)

cleanlib:
	make fclean -C $(LIB_DIR)

$(LIBFT):
	make -re -C $(LIB_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@rm -f $(TEST_OBJ)

fclean: clean cleanlib
	@rm -f $(NAME)

re: fclean all
