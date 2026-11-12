# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 15:19:42 by tat-nguy          #+#    #+#              #
#    Updated: 2026/10/23 11:28:47 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME		= libft.a

DIR_SRCS	= srcs
DIR_OBJS	= objs
SUBDIRS		= is lst mem put str to ft_printf gnl math

# Paths and Files
SRCS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_SRCS)/, $(dir)))
OBJS_DIRS	= $(foreach dir, $(SUBDIRS), $(addprefix $(DIR_OBJS)/, $(dir)))

SRCS		= $(foreach dir, $(SRCS_DIRS), $(wildcard $(dir)/*.c))
OBJS		= $(subst $(DIR_SRCS), $(DIR_OBJS), $(SRCS:.c=.o))

INCLUDES	= -I includes

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar -rc
RANLIB		= ranlib
RM			= rm -rf
CR_DIR		= mkdir -p

# Rules
$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c
			@$(CR_DIR) $(OBJS_DIRS)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)
			@$(RANLIB) $(NAME)

clean:
			@$(RM) $(OBJS)
			@$(RM) $(DIR_OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
