CC:=cc
CFLAGS := -Wall -Wextra -Werror
SRC := ft_utils.c \
	   ft_printf.c \
	   ft_putnbr.c \
	   ft_puthex.c \

OBJ := $(patsubst %.c, %.o, $(SRC))

NAME := libftprintf.a

GREEN    := \033[32m
RESET    := \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $^
	@printf "$(GREEN)$(NAME) created successfully!$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -I. -c -o $@ $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
