# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <snunes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 12:37:58 by snunes            #+#    #+#              #
#    Updated: 2019/08/21 11:42:33 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
NAME = ft_ls
VPATH = .:include:src

SRC = 		ft_ls.c \
			fill_tree.c \
			option_l.c \
			print.c \
			utils.c \
			avl_tree.c \
			free.c \
			option_recurs.c \
			error.c \
			option_t.c

LDFLAG = -Llibft
LDLIB = -lft
OBJ_PATH = obj
I_PATH = include
HEADER = ft_ls.h ft_printf.h libft.h
OBJ_NAME = $(SRC:.c=.o)
CCFLAGS = -Wall -Wextra -Werror -g
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CLINE = \033[K
CLEAR = \033[0m
GREEN = \033[32m
BYELLOW = \033[33;1m
RED = \033[31m

.PHONY : all, clean, fclean, re, help, norme

## all		: compile et cree l'executable
all : $(NAME)

$(NAME) ::
	@cd libft/ && $(MAKE)

$(NAME) :: $(OBJ)
	@echo "$(BYELLOW)Generating $(RED)$@$(CLEAR)"
	@$(CC) $(CCFLAGS) -o $@ $^ -I $(I_PATH) $(LDFLAG) $(LDLIB) 
	@echo "$(GREEN)[DONE]$(CLEAR)"

## objet		: verifie que les objets et le header soient a jour
$(OBJ_PATH)/%.o : %.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true 
	@$(CC) $(CCFLAGS) -I $(I_PATH) -o $@ -c $< 
	@echo "$(GREEN)[OK]\t$(BYELLOW)Compiling$(CLEAR) $<"

## clean		: efface tout les binaires
clean :
	@cd libft && $(MAKE) $@
	@echo "$(RED)Cleaning all binaries$(CLEAR)"
	@rm -f $(OBJ)
	@echo "$(RED)Removing binaries folder$(CLEAR)"
	@rm -rf $(OBJ_PATH) 2> /dev/null || true

## fclean		: efface les binaires ainsi que l'executable
fclean : clean
	@echo "$(RED)Deleting libft.a$(CLEAR)"
	@cd libft && rm -f libft.a
	@echo "$(RED)Deleting $(NAME)$(CLEAR)"
	@rm -f $(NAME)

## re		: lance la regle "fclean", puis la regle "all"
re : fclean all

## norme		: verifie la norme du projet
norme :
	@norminette $(SRC)
	@norminette $(HEADER)

## help		: affiche les options disponibles et leurs utilitees
help : Makefile
	@sed -n 's/^##//p' $<
