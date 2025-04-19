# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trupham <trupham@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 11:45:16 by trupham           #+#    #+#              #
#    Updated: 2025/04/15 12:15:54 by trupham          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS = -Wall -Wextra -Werror
SRC_PATH = .
SRC = $(foreach D, $(SRC_PATH), $(wildcard $(D)/*.c))
OBJ = $(patsubst %.c, %.o, $(SRC))

NAME = libft.a

GREEN    = \033[32m
RESET    = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $^
	@printf "$(GREEN)libft.a created successfully!$(RESET)"

$(SRC_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -I. -c -o $@ $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
