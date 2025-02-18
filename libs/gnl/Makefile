# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 14:19:03 by ebonutto          #+#    #+#              #
#    Updated: 2025/02/18 14:27:40 by ebonutto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a
CC = cc
CFLAGS = -Werror -Wextra -Wall
AR = ar rcs
SRC_PATH = src_gnl/
SRC_BONUS_PATH = src_bonus_gnl/
OBJ_PATH = obj_gnl/
INCLUDE = -I include_gnl -I $(LIBFT_PATH)/include_libft

LIBFT_PATH = ./../libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC = get_next_line.c \
		get_next_line_utils.c

SRC_BONUS = get_next_line_bonus.c \
				get_next_line_utils_bonus.c

OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
OBJ_BONUS = $(addprefix $(OBJ_PATH), $(SRC_BONUS:.c=.o))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_PATH)%.o: $(SRC_BONUS_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(LIBFT):
	make -sC $(LIBFT_PATH) all

$(NAME): $(LIBFT) $(OBJ)
	$(AR) $@ $(OBJ)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re
