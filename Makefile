# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dufama <dufama@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/20 17:22:56 by dufama            #+#    #+#              #
#    Updated: 2026/02/20 17:44:58 by dufama           ###   ########.fr        #
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

SRCS_PARSING = parsing/read_map.c \

SRCS_MAIN = main.c

SRCS_FILES = $(SRCS_MAIN) $(SRCS_PARSING)

SRCS = $(addprefix $(OBJ_DIR), $(SRCS_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRCS_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(Y)--- Finalizing Compilation ---$(R)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(G)✅ $(NAME) created successfully!$(R)"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(B)🔨 Compiling: $< $(R)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(G)[OK]$(R)"

clean:
	@echo "$(Y)Cleaning objects...$(R)"
	@rm -rf $(OBJ_DIR)
	@echo "$(G)Objects cleaned.$(R)"

fclean: clean
	@echo "$(Y)Removing $(NAME)...$(R)"
	@rm -f $(NAME)
	@echo "$(G)Cleanup complete.$(R)"

re: fclean all

.PHONY: all clean fclean re
