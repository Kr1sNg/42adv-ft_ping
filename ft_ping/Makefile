# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/19 21:54:58 by tat-nguy          #+#    #+#              #
#    Updated: 2026/10/19 23:18:58 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ***** Color Definition ***** #

RED 	= \033[91m
YELLOW 	= \033[33m
GREEN 	= \033[92m
RESET 	= \033[0m

# **************************** #

NAME = ft_ping

# Source Files
SRC   		= src/main.c \
						src/parse.c \
						src/print.c \
				
# Object Files
OBJS 		= $(SRC:.c=.o)

# Include and Flags
CC 				= cc
INCLUDE 	= -Iincludes
CFLAGS 		= -Wall -Wextra -Werror
RM				= rm -rf

# Target
all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YELLOW) 🛠️  waiting for compilation...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(INCLUDE) $(CFLAGS)
	@echo "$(GREEN) 🤖  Compiled successful ✴️  $(NAME) ✴️$(RESET)"
	
# Clean
clean:
	@$(RM) $(OBJS)
	@echo "$(RED) 🗑️  Deleted object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED) 🚽  Deleted ❄️  $(NAME) ❄️$(RESET)"

re: fclean all

bonus: re

.PHONY: all clean fclean re bonus