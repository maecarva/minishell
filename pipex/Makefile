# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 14:19:08 by ebonutto          #+#    #+#              #
#    Updated: 2025/01/29 15:49:44 by ebonutto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Werror -Wextra -Wall -g3
SRC_PATH = src_pipex/
SRC_BONUS_PATH = src_bonus_pipex/
OBJ_PATH = obj_pipex/
INCLUDE = -I include_pipex -I $(GNL_PATH)/include_gnl -I $(LIBFT_PATH)/include_libft

LIBS_PATH = libs

GNL_PATH = $(LIBS_PATH)/gnl
GNL = $(GNL_PATH)/gnl.a

LIBFT_PATH = $(LIBS_PATH)/libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC_COMMON = exec.c \
					here_doc.c \
					init.c \
					parent_first.c \
					parent_last.c \
					pipex_utils.c \

SRC = $(SRC_COMMON) pipex.c
SRC_BONUS = $(SRC_COMMON) init_bonus.c parent_mid.c pipex_bonus.c

OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
OBJ_BONUS = $(addprefix $(OBJ_PATH), $(SRC_BONUS:.c=.o))

all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_PATH)%.o: $(SRC_BONUS_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(LIBFT):
	@make -sC $(LIBFT_PATH) extra

$(GNL): $(LIBFT)
	@make -sC $(GNL_PATH)

$(NAME): $(LIBFT) $(GNL) $(OBJ)
	@$(CC) $(CFLAGS) -o $@  $(OBJ) $(GNL) $(LIBFT) $(INCLUDE)

$(NAME_BONUS): $(LIBFT) $(GNL) $(OBJ_BONUS)
	@$(CC) $(CFLAGS) -o $@  $(OBJ_BONUS) $(GNL) $(LIBFT) $(INCLUDE)

clean:
	@make -sC $(LIBFT_PATH) clean
	@make -sC $(GNL_PATH) clean
	@rm -rf $(OBJ_PATH)

fclean: clean
	@make -sC $(LIBFT_PATH) fclean
	@make -sC $(GNL_PATH) fclean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
