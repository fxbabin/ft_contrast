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
NAME2			=   ft_contrast_th
NAME3			=   ft_contrast_tp

COMMON 			=	utils contrast read_content check
CONT			=	ft_contrast
CONTH			=	ft_contrast_th
CONTP 			=	ft_contrast_tp

SRC_COM			=	srcs_contrast
SRC				=	$(patsubst %, $(SRC_COM)/%.c, $(COMMON))

SRC_CONT   		=	srcs_contrast
SRC_C 			=   $(patsubst %, $(SRC_CONT)/%.c, $(CONT))
SRC_C			+=  $(SRC)

SRC_CONTH   	=	srcs_contrast_th
SRC_CTH 		=   $(patsubst %, $(SRC_CONTH)/%.c, $(CONTH))
SRC_CTH			+=  $(SRC)

SRC_CONTP   	=	srcs_contrast_tp
SRC_CTP 		=   $(patsubst %, $(SRC_CONTP)/%.c, $(CONTP))
SRC_CTP			+=  $(SRC)

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g3

INCLUDES		=	includes
SRC_DIR			=	srcs_contrast
OBJ_DIR			=	obj

OBJS_C			=	$(SRC_C:.c=.o)
OBJS_CTH		=	$(SRC_CTH:.c=.o)
OBJS_CTP		=	$(SRC_CTP:.c=.o)

_LIBFT			=	libft.a
LIB_DIR			= 	libft
LIB 			= 	$(patsubst %, $(LIB_DIR)/, $(_LIBFT))
HEADER			= 	$(INCLUDES)/ft_tpool.h

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: libft/libft.a $(HEADER) $(NAME) $(NAME2) $(NAME3)

$(NAME): $(LIB) $(OBJS_C)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS_C) -L$(LIB_DIR) -lft
		@echo $@ ": $(_GREEN)Done$(_END)"

$(NAME2): $(LIB) $(OBJS_CTH)
		@$(CC) $(CFLAGS) -o $(NAME2) $(OBJS_CTH) -L$(LIB_DIR) -lft
		@echo $@ ": $(_GREEN)Done$(_END)"

$(NAME3): $(LIB) $(OBJS_CTP)
		@$(CC) $(CFLAGS) -o $(NAME3) $(OBJS_CTP) -L$(LIB_DIR) -lft
		@echo $@ ": $(_GREEN)Done$(_END)"

$(OBJ_DIR):
		@mkdir -p $@
		@echo $@ ": $(_GREEN)Done$(_END)"

%.o : %.c $(INCLUDES)/ft_tpool.h
		@$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)
		@echo $@ ": $(_GREEN)Done$(_END)"

libft/libft.a:
		@make -C $(LIB_DIR)

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(OBJS_C)
		@/bin/rm -f $(OBJS_CTH)
		@/bin/rm -rf $(OBJ_DIR)
		@echo $@ ": $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(NAME)
		@/bin/rm -f $(NAME2)
		@echo $@ ": $(_GREEN)Done$(_END)"

re: fclean all

.PHONY: all clean fclean re
