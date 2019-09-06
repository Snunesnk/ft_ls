# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <snunes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 12:37:58 by snunes            #+#    #+#              #
#    Updated: 2019/09/06 12:47:29 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
NAME = ft_ls
VPATH = .:include:src/options:src/binary_tree:src/main_func:src/utils:libft

SRC = 		ft_ls.c \
			fill_tree.c \
			option_l.c \
			print.c \
			utils.c \
			avl_tree.c \
			free.c \
			option_recurs.c \
			error.c \
			option_t.c \
			ft_filequ.c \
			first_tree.c \
			option_t2.c

SRC_PATH = src
LDFLAGS = -Llibft
LDLIB = -lft
LIB = libft/libft.a
OBJ_PATH = obj
I_PATH = include
HEADER = ft_ls.h ft_printf.h libft.h
OBJ_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
CCFLAGS = -Wall -Wextra -Werror -g3

CURSOR = \033[1A
LCLEAR = \033[2K
CLEAR = \033[0m
GREEN = \033[32m
BGREEN = \033[32;1m
BYELLOW = \033[33;1m
BWHITE = \033[37;1m
BCYAN = \033[36;1m
RED = \033[31m

.PHONY : all, clean, fclean, re, help, norme

## all		: compile et cree l'executable
all : $(NAME)

$(NAME) ::
	@cd libft/ && $(MAKE)

$(NAME) :: $(OBJ) $(LIB)
	@echo "$(LCLEAR)$(BCYAN)$@$(BWHITE) => $(BGREEN)[done]$(CLEAR)"
	@$(CC) $(CCFLAGS) -o $@ $^ -I $(I_PATH) $(LDFLAGS) $(LDLIB) 

## objet		: verifie que les objets et le header soient a jour
$(OBJ_PATH)/%.o : %.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CCFLAGS) -I $(I_PATH) -o $@ -c $< 
	@echo "$(LCLEAR)$(BWHITE)[Compiling] =>$(CLEAR) $<$(CLINE)$(CURSOR)"

## clean		: efface tout les binaires
clean :
	@cd libft && $(MAKE) $@
	@echo "$(RED)Deleting $(NAME) obj$(CLEAR)$(CURSOR)"
	@rm -f $(OBJ)
	@echo "$(LCLEAR)$(RED)Deleting $(NAME) obj folder$(CLEAR)$(CURSOR)"
	@rm -rf $(OBJ_PATH) 2> /dev/null || true

## fclean		: efface les binaires ainsi que l'executable
fclean : clean
	@echo "$(LCLEAR)$(RED)Deleting libft.a$(CLEAR)$(CURSOR)"
	@cd libft && rm -f libft.a
	@echo "$(LCLEAR)$(RED)Deleting $(NAME)$(CLEAR)"
	@rm -f $(NAME)

## re		: lance la regle "fclean", puis la regle "all"
re : fclean all

## norme		: verifie la norme du projet
norme :
	@norminette $(SRC_PATH) | grep -B1 --colour=auto "Error" || true
	@norminette $(I_PATH) | grep -B1 --colour=auto "Error" || true
	@cd libft && $(MAKE) $@

## help		: affiche les options disponibles et leurs utilitees
help : Makefile
	@sed -n 's/^##//p' $<
