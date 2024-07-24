# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tanselmo <tanselmo@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:01:48 by tanselmo          #+#    #+#              #
#    Updated: 2024/07/24 18:14:33 by tanselmo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = src

OBJ_DIR = obj

FILES = src/philo.c \
src/init.c \
src/atoi.c \
src/threads.c \
src/utils.c \

CC = clang

CFLAGS = -g -Wall -Werror -Wextra -pthread #-fsanitize=thread

OBJS_SRCS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(FILES))

NAME = philo

INCLUDE = -I $(SRCS_DIR)

RM = rm -rf

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

#Rules

$(NAME): $(OBJS_SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE) $(OBJS_SRCS) -o $(NAME)

clean:
	@$(RM) $(OBJ_DIR) clean

fclean: clean
	@$(RM) $(NAME) fclean

re: fclean all

.PHONY: all clean fclean re