# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgoldenb <sgoldenb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 20:16:10 by sgoldenb          #+#    #+#              #
#    Updated: 2024/08/08 20:11:58 by sgoldenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include custom.mk

MAKEFLAGS += --silent

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -O3
F_FLAGS = -fsanitize=address -g

SRC_DIR = src
INC_DIR = .

SRCS = philo.c init.c monitoring.c operations.c ft_atoi.c routine.c ft_arrfree.c ft_arrlen.c ft_intlen.c ft_isdigit.c ft_strlen.c malloc_phi_mutex.c print_state.c routine_utils.c sync_utils.c utils.c
OBJS = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

all: $(NAME)
	
$(NAME): norminette $(OBJS)
	@echo "\n$(INFO_MESSAGE)Compilation philosophers"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) || { echo "$(ERROR_MESSAGE)Erreur de compilation philosophers"; exit $?; }
	@echo "$(SUCCESS_MESSAGE)philosophers OK\n"

test_t: norminette $(OBJS)
	@echo "\n$(INFO_MESSAGE)Compilation philosophers"
	$(CC) $(CFLAGS) $(F_FLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) || { echo "$(ERROR_MESSAGE)Erreur de compilation philosophers"; exit $?; }
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
	norminette $(INC_DIR)/philo_utils.h
	norminette $(INC_DIR)/philo.h
	@echo "$(SUCCESS_MESSAGE)NORME OK\n"

clean:
	@echo "$(INFO_MESSAGE)Nettoyage des objets"
	rm -f $(OBJS)
	@echo "$(SUCCESS_MESSAGE)Nettoyage objets OK\n"

fclean:
	@echo "$(INFO_MESSAGE)Nettoyage programmes & librairies"
	rm -f $(NAME) || $(ERROR_EXIT) "Erreur lors du nettoyage programme"
	@echo "$(SUCCESS_MESSAGE)Nettoyage programmes & librairies OK\n"

re: clean all

.PHONY: all fclean clean
.DEFAULT_GOAL = all