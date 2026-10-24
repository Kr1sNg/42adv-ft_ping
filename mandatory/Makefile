# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/19 21:54:58 by tat-nguy          #+#    #+#              #
#    Updated: 2026/10/23 16:45:41 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ***** Color Definition ***** #

RED 	= \033[91m
YELLOW 	= \033[33m
GREEN 	= \033[92m
RESET 	= \033[0m

# **************************** #

NAME = ft_ping

# Libft
LIBFT_DIR	= ./libft
LIBFT			= $(LIBFT_DIR)/libft.a

# Source Files
SRC   		= src/main.c \
						src/icmp.c \
						src/loop.c \
						src/network.c \
						src/parse.c \
						src/print.c \
						src/receive.c \
						src/signal.c \
						src/time.c \
				
# Object Files
OBJS 		= $(SRC:.c=.o)

# Include and Flags
CC 				= cc
INCLUDE 	= -Iincludes
CFLAGS 		= -Wall -Wextra -Werror
RM				= rm -rf
LIBFLAGS	= -L$(LIBFT_DIR) -lft

# Target
all: $(LIBFT) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW) 🛠️  waiting for compilation...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(INCLUDE) $(CFLAGS) $(LIBFLAGS)
	@echo "$(GREEN) 🤖  Compiled successful ✴️  $(NAME) ✴️$(RESET)"
	
# Clean
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "$(RED) 🗑️  Deleted object files.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(RED) 🚽  Deleted ❄️  $(NAME) ❄️$(RESET)"

re: fclean all

bonus: re

.PHONY: all clean fclean re bonus