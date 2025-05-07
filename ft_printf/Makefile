CC:=cc
#WARN:remove fsanitize before submit
CFLAGS := -Wall -Wextra -Werror -fsanitize=address
SRC := utils.c \
	   ft_printf.c \
	   test.c \

OBJ := $(patsubst %.c, %.o, $(SRC))

NAME := libftprintf.a
TEST := test.out

GREEN    := \033[32m
RESET    := \033[0m

all: $(NAME)

test: $(TEST)
	@./$(TEST)

$(TEST): $(OBJ)
	@$(CC) $(CFLAGS) -I. $^ -o $@

$(NAME): $(OBJ)
	@ar rcs $@ $^
	@printf "$(GREEN)$(NAME) created successfully!$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -I. -c -o $@ $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re
