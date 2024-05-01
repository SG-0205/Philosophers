# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 20:16:10 by sgoldenb          #+#    #+#              #
#    Updated: 2024/05/01 20:03:56 by sgoldenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include inc/custom.mk

MAKEFLAGS += --silent

NAME = philosophers
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -Lincludes/libft

SRC_DIR = src
INC_DIR = inc

SRCS = philosophers.c
OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

test:
	cc -Wall -Wextra -Werror src/*.c inc/utils/*.c -g -o philotest

test_t:
	cc -Wall -Wextra -Werror -pthread -fsanitize=address src/*.c inc/utils/*.c -g -o philotest
	
$(NAME): norminette libft $(OBJS)
	@echo "\n$(INFO_MESSAGE)Compilation philosophers"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) || { echo "$(ERROR_MESSAGE)Erreur de compilation philosophers"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)philosophers OK\n"

%.o: %.c
	@if [ -z "$?" ]; then \
		echo "$(INFO_MESSAGE)Fichiers sources identiques, aucun changement."; \
		exit $?; \
	else \
		echo "\t$<"; \
		$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ || { echo "\t$(COMP_KO)"; exit $?; }; \
		echo "\t$(COMP_OK)"; \
	fi

norminette:
	norminette $(SRC_DIR)
	norminette $(INC_DIR)/libft
	norminette $(INC_DIR)/philosophers.h
	@echo "$(SUCCESS_MESSAGE)NORME OK\n"

libft:
	@echo "$(INFO_MESSAGE)Compilation libft"
	make all -C includes/libft 2>/dev/null || { echo "$(ERROR_MESSAGE)Erreur de compilation LIBFT"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)LIBFT OK\n"

clean:
	@echo "$(INFO_MESSAGE)Nettoyage des objets"
	rm -f $(OBJS) || $(ERROR_EXIT) "Erreur lors du nettoyage objet"
	make clean -C includes/libft 2>/dev/null || { echo "$(ERROR_MESSAGE)Erreur lors du nettoyage objet"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)Nettoyage objets OK\n"

fclean:
	@echo "$(INFO_MESSAGE)Nettoyage programmes & librairies"
	rm -f $(NAME) || $(ERROR_EXIT) "Erreur lors du nettoyage programme"
	make fclean -C includes/libft || { echo "$(ERROR_MESSAGE)Erreur lors du nettoyage des librairies"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)Nettoyage programmes & librairies OK\n"

re: clean all

.PHONY: all fclean clean
.DEFAULT_GOAL = all