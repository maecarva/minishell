# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 14:19:08 by ebonutto          #+#    #+#              #
#    Updated: 2025/02/09 15:52:14 by maecarva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                              VARIABLES PROGRAM                               #
################################################################################

# Nom du programme final
NAME = minishell

# Compilateur et flags de compilation
CC = cc
CFLAGS = -Werror -Wextra -Wall -g

################################################################################
#                              DIRECTORY PATHS                                 #
################################################################################

# Chemins des sources et objets
SRC_PATH = src_minishell/
OBJ_PATH = obj_minishell/

# Dossier des bibliothèques externes
LIBS_PATH = libs
GNL_PATH = $(LIBS_PATH)/gnl
LIBFT_PATH = $(LIBS_PATH)/libft

################################################################################
#                              FICHIERS SOURCES                                #
################################################################################

# Liste des fichiers sources
SRC = src_minishell/main.c \
	  src_minishell/init/init.c \
	  src_minishell/init/env.c \
	  src_minishell/init/env_utils.c \
	  src_minishell/clear/clear.c \
	  src_minishell/signals/signals.c \
	  src_minishell/parsing/parsing.c \
	  src_minishell/parsing/ast_constructor.c \
	  src_minishell/parsing/create_node.c \
	  src_minishell/parsing/ast_clear.c \
	  src_minishell/parsing/rules.c \
	  src_minishell/parsing/parser/parser.c \
	  src_minishell/parsing/lexer/lexer.c \
	  src_minishell/parsing/lexer/spliter.c \
	  src_minishell/parsing/lexer/lexer_utils.c \
	  src_minishell/parsing/expander/expander.c \
	  src_minishell/parsing/ast/ast.c \
	  src_minishell/parsing/ast/command_node.c \
	  src_minishell/parsing/ast/pipe_node.c \
	  src_minishell/builtin/echo.c \
	  src_minishell/pipes/execute_command.c \
	  src_minishell/pipes/first_parent.c \
	  src_minishell/pipes/infinite_parent.c \
	  src_minishell/pipes/last_parent.c \
	  src_minishell/pipes/pipes_utils.c \
	  src_minishell/pipes/pipes.c \
	  src_minishell/pipes/simple_command.c \
	  src_minishell/check_type_execute.c


SRC += $(SRC_PIPES)
# Conversion des .c en .o dans le dossier obj
OBJ = $(SRC:.c=.o)

################################################################################
#                              INCLUDES AND LIBRARIES                          #
################################################################################

# Headers
INCLUDE = -I include_minishell -I $(GNL_PATH)/include_gnl -I $(LIBFT_PATH)/include_libft

# Bibliothèques statiques
GNL = $(GNL_PATH)/gnl.a
LIBFT = $(LIBFT_PATH)/libft.a

################################################################################
#                              COMPILING RULES                                 #
################################################################################

# Règle par défaut
all: $(NAME)

# Alias pour la règle all
bonus: all

# Compilation des fichiers sources en objets
%.o: %.c
	# mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

# Compilation des fichiers bonus en objets
$(OBJ_PATH)%.o: $(SRC_BONUS_PATH)%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

################################################################################
#                              COMPILING LIBS                                  #
################################################################################

# Compilation de la libft
$(LIBFT):
	make -sC $(LIBFT_PATH) all

# Compilation de la GNL (dépend de la libft)
$(GNL): $(LIBFT)
	make -sC $(GNL_PATH)

################################################################################
#                              CREATING THE EXECUTABLE                         #
################################################################################

# Création de l'exécutable final
$(NAME): $(LIBFT) $(GNL) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(GNL) $(LIBFT) $(INCLUDE) -lreadline

################################################################################
#                              	CLEANING RULES                                 #
################################################################################

# Suppression des fichiers objets
clean:
	make -sC $(LIBFT_PATH) clean
	make -sC $(GNL_PATH) clean
	rm -rf $(OBJ)

# Suppression des fichiers objets et des exécutables
fclean: clean
	make -sC $(LIBFT_PATH) fclean
	make -sC $(GNL_PATH) fclean
	rm -f $(NAME)

# Recompilation complète
re: fclean all

# Déclaration des règles spéciales
.PHONY: all clean fclean re bonus
