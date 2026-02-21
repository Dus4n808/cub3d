# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/20 17:22:56 by dufama            #+#    #+#              #
#    Updated: 2026/02/21 14:32:29 by dufama           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

G = \033[0;32m
B = \033[0;34m
Y = \033[0;33m
R = \033[0m

NAME = cub3d
CC = cc
CFLAGS = -Wall -Werror -Wextra -I include/
SRCS_DIR = srcs/
OBJ_DIR = obj/

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_PARSING = parsing/read_map.c \

SRCS_MAIN = main.c

SRCS_FILES = $(SRCS_MAIN) $(SRCS_PARSING)

SRCS = $(addprefix $(OBJ_DIR), $(SRCS_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRCS_FILES:.c=.o))

TEST_SRCS = tests/test_main.c \
			tests/test_parsing.c \

TEST_OBJS = $(filter-out $(OBJ_DIR)main.o, $(OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(Y)--- Finalizing Compilation ---$(R)"
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(G)✅ $(NAME) created successfully!$(R)"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(B)🔨 Compiling: $< $(R)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(G)[OK]$(R)"

clean:
	@echo "$(Y)Cleaning objects...$(R)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "$(G)Objects cleaned.$(R)"

fclean: clean
	@echo "$(Y)Removing $(NAME)...$(R)"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(G)Cleanup complete.$(R)"

re: fclean all

test: $(OBJS)
	@echo "🧪 Running tests..."
	@$(CC) $(CFLAGS) $(TEST_SRCS) $(TEST_OBJS) $(LIBFT) -o test_bin
	@./test_bin
	@rm -f test_bin

.PHONY: all clean fclean re
