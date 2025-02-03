# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 14:24:44 by ebonutto          #+#    #+#              #
#    Updated: 2025/02/03 10:07:22 by ebonutto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Werror -Wall -Wextra
AR = ar rcs
SRC_PATH = src_libft/
SRC_LINKED_LIST_PATH = src_linked_list_libft/
SRC_BINARY_TREE_PATH= src_binary_tree_libft/
SRC_EXTRA_PATH = src_extra_libft/
OBJ_PATH = obj_libft/
INCLUDE = -I include_libft

SRC = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c

SRC_LINKED_LIST = ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c

SRC_BINARY_TREE = ft_btree_create_node.c \
					ft_btree_apply_prefix.c \
					ft_btree_apply_infix.c \
					ft_btree_apply_suffix.c \
					ft_btree_insert_data.c \
					ft_btree_search_item.c \
					ft_btree_level_count.c

SRC_EXTRA = ft_abs.c \
			ft_close.c \
			ft_error.c \
			ft_free_double_ptr.c \
			ft_free_simple_ptr.c \
			ft_issign.c \
			ft_isspace.c \
			ft_max.c \
			ft_min.c \
			ft_only_space.c \
			ft_perror.c \
			ft_str_three_join.c \
			ft_swap.c

OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o) $(SRC_LINKED_LIST:.c=.o) $(SRC_EXTRA:.c=.o) $(SRC_BINARY_TREE:.c=.o))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_PATH)%.o: $(SRC_LINKED_LIST_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_PATH)%.o: $(SRC_BINARY_TREE_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(OBJ_PATH)%.o: $(SRC_EXTRA_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME): $(OBJ)
	$(AR) $@ $^

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
