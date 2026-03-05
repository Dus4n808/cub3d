# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/20 17:22:56 by dufama            #+#    #+#              #
#    Updated: 2026/03/05 16:30:26 by dufama           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

G = \033[0;32m
B = \033[0;34m
Y = \033[0;33m
R = \033[0m

NAME = cub3d
CC = cc -g
CFLAGS = -Wall -Werror -Wextra -I include/
SRCS_DIR = srcs/
OBJ_DIR = obj/

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	MLX_DIR = ./mlx-mac
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR = ./mlx-linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif

CFLAGS += -I$(MLX_DIR)

SRCS_PARSING = parsing/read_file.c \
				parsing/parse_file.c \
				parsing/parse_elements.c \
				parsing/parse_map.c \
				parsing/check_elements.c \
				parsing/check_map.c

SRCS_RENDER = render/game.c \
				render/draw.c \
				render/raycasting.c \
				render/player.c \
				render/move.c \
				render/textures.c

SRCS_MAIN = main.c

SRCS_FILES = $(SRCS_MAIN) $(SRCS_PARSING) $(SRCS_RENDER) utils.c

SRCS = $(addprefix $(OBJ_DIR), $(SRCS_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRCS_FILES:.c=.o))

TEST_SRCS = tests/test_main.c \
			tests/test_parsing.c \

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(Y)--- Finalizing Compilation ---$(R)"
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(MAKE) -s -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
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
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo "$(G)Objects cleaned.$(R)"

fclean: clean
	@echo "$(Y)Removing $(NAME)...$(R)"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(G)Cleanup complete.$(R)"

re: fclean all

test: $(OBJS)
	@echo "🧪 Running tests..."
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(TEST_SRCS) $(LIBFT) -o test_bin
	@./test_bin
	@rm -f test_bin

debug_parsing:
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(CC) -g3 -fsanitize=address -I include/ \
		srcs/main.c \
		srcs/parsing/read_file.c \
		srcs/parsing/parse_file.c \
		srcs/parsing/parse_elements.c \
		srcs/utils.c \
		$(LIBFT) -o cub3d_debug

.PHONY: all clean fclean re
