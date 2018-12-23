# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/21 20:52:27 by fbabin            #+#    #+#              #
#    Updated: 2018/12/21 20:52:35 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ft_contrast
PUSH_SWAP		=   push_swap

FNT				=	ft_contrast ft_queue contrast read_content check

CC				=	gcc
FLAGS			=	-Wall -Werror -Wextra

INCLUDES		=	includes
SRC_DIR			=	srcs_contrast
OBJ_DIR			=	obj

SRC				=	$(patsubst %, $(SRC_DIR)/%.c, $(FNT))
OBJ				=	$(patsubst %, $(OBJ_DIR)/%.o, $(FNT))
_LIBFT			=	libft.a
LIB_DIR			= 	libft
LIB 			= 	$(patsubst %, $(LIB_DIR)/, $(_LIBFT))
HEADER			= 	$(INCLUDES)/ft_tpool.h

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: lib $(HEADER) $(NAME)

$(NAME): $(LIB) $(OBJ)
		@$(CC) -fsanitize=address $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIB_DIR) -lft
		@echo $@ ": $(_GREEN)Done$(_END)"

$(OBJ_DIR):
		@mkdir -p $@
		@echo $@ ": $(_GREEN)Done$(_END)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INCLUDES)/ft_tpool.h | $(OBJ_DIR)
		@$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)
		@echo $@ ": $(_GREEN)Done$(_END)"

lib:
		@make -C $(LIB_DIR)

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(OBJ)
		@/bin/rm -rf $(OBJ_DIR)
		@echo $@ ": $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(NAME)
		@echo $@ ": $(_GREEN)Done$(_END)"

re: fclean all

.PHONY: all clean fclean re
