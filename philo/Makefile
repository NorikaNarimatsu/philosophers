# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 13:08:54 by nnarimat          #+#    #+#              #
#    Updated: 2024/08/22 16:08:09 by nnarimat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3
SRC_DIR = src
OBJ_DIR = obj
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/input.c  $(SRC_DIR)/libft.c \
		  $(SRC_DIR)/init.c  $(SRC_DIR)/time.c $(SRC_DIR)/routine.c \
		  $(SRC_DIR)/monitor.c $(SRC_DIR)/print.c $(SRC_DIR)/clean.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
