# ***** Color Definition ***** #

RED 	= \033[91m
YELLOW 	= \033[33m
GREEN 	= \033[92m
RESET 	= \033[0m

# **************************** #

NAME = ft_ping

# Libft
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Source Files
SRC     	= src/main/animation.c src/main/main.c \
				src/parsing/error_map.c \
				src/parsing/free_map.c \
				
# Object Files
OBJS 		= $(SRC:.c=.o)

# Include and Flags
INCLUDE 	= -Iincludes
CFLAGS 		= -Wall -Wextra -Werror -I/usr/X11/include -g
CC 			= cc
RM			= rm -rf
LIBFLAGS	= -L$(LIBFT_DIR) -lft

# Target
all: $(LIBFT) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW) 🛠️  waiting for compilation...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(INCLUDE) $(CFLAGS) $(LIBFLAGS) -lm
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

