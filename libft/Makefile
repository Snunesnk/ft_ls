# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snunes <snunes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 12:37:58 by snunes            #+#    #+#              #
#    Updated: 2019/08/02 12:35:38 by snunes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
VPATH = .:ft_is:ft_mem:ft_printf/conversions:ft_printf/double: \
			ft_printf/main_func:ft_printf/print:ft_str:ft_lst:ft_put

SRC = ft_putchar.c ft_putstr.c ft_putchar_fd.c ft_putstr_fd.c ft_isdigit.c \
		ft_isalpha.c ft_bzero.c ft_memalloc.c ft_memdel.c ft_strlen.c \
		ft_strnew.c ft_strcat.c ft_strcpy.c ft_strsub.c ft_atoi.c ft_putnbr.c \
		ft_memcpy.c ft_lstdel.c ft_lstdelone.c ft_lstadd.c ft_lstnew.c \
		ft_putnbr_fd.c ft_lstiter.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_itoa.c ft_memccpy.c ft_lstmap.c ft_memmove.c \
		ft_memset.c ft_putendl_fd.c ft_putendl.c ft_tolower.c ft_toupper.c \
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strdel.c ft_strdup.c ft_strequ.c\
		ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strmap.c \
		ft_strmapi.c ft_strncat.c ft_strncpy.c ft_strnequ.c ft_strnstr.c \
		ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strtrim.c ft_memchr.c \
		ft_memcmp.c ft_isspace.c ft_strncmp.c ft_isupcase.c ft_strjoin_free.c \
		ft_strndup.c ft_strjoin_fclr.c ft_abs.c ft_islowcase.c get_next_line.c \
		ft_lst_length.c ft_sqrt.c ft_strrev.c ft_nbrlen.c ft_nbrrev.c \
		ft_putlongnbr.c ft_printf.c lst_func_1.c lst_func_2.c lst_func_3.c \
		get_flags.c print_multi.c arrange_flags.c ft_nblen.c deal_wdouble.c \
		exept_double.c big_int.c print_csp.c handle_flags.c deal_w_l_double.c \
		handle_colors.c init_arrays.c ft_dprintf.c ft_occur.c

OBJ_PATH = obj
I_PATH = ../include
HEADER_NAME = libft.h ft_printf.h
OBJ_NAME = $(SRC:.c=.o)
CCFLAGS = -Wall -Wextra -Werror
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
HEADER = $(addprefix $(I_PATH)/,$(HEADER_NAME))

CLEAR = \033[0m
GREEN = \033[32m
BYELLOW = \033[33;1m
RED = \033[31m

.PHONY : all, clean, fclean, re, help, norme

## all		: compile et cree l'executable
all : $(NAME)

$(NAME) : $(OBJ)
	@echo "$(BYELLOW)Generating $(CLEAR)$(RED)$@$(CLEAR)"
	@ar -rc $@ $^
	@ranlib $@
	@echo "$(GREEN)[DONE]$(CLEAR)"

## objet		: verifie que les objets et le header soient a jour
$(OBJ_PATH)/%.o : %.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CCFLAGS) -I $(I_PATH) -o $@ -c $<
	@echo "$(GREEN)[OK]\t$(BYELLOW)Compiling$(CLEAR) $<"

## clean		: efface tout les binaires
clean :
	@echo "$(RED)Cleaning all binaries$(CLEAR)"
	@rm -f $(OBJ)
	@echo "$(RED)Removing binaries folder$(CLEAR)"
	@rmdir $(OBJ_PATH) 2> /dev/null || true

## fclean		: efface les binaires ainsi que l'executable
fclean : clean
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
